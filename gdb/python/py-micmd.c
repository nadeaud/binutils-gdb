/* gdb MI commands implemented in Python  */

#include <string.h>

#include "defs.h"
#include "arch-utils.h"
#include "value.h"
#include "python-internal.h"
#include "charset.h"
#include "gdbcmd.h"
#include "cli/cli-decode.h"
#include "completer.h"
#include "language.h"
#include "mi/mi-cmds.h"

struct micmdpy_object
{
  PyObject_HEAD
};

typedef struct micmdpy_object micmdpy_object;

static PyObject *invoke_cst;

extern PyTypeObject micmdpy_object_type
  CPYCHECKER_TYPE_OBJECT_FOR_TYPEDEF ("micmdpy_object");

/* If the command invoked returns a list, this function parses it and create an
   appropriate MI out output.

   The returned values must be Python string, and can be contained within Python
   lists and dictionaries. It is possible to have a multiple levels of lists
   and/or dictionaries.  */

static void
parse_mi_result (PyObject *result, const char *field_name)
{
  struct ui_out *uiout = current_uiout;

  if(!field_name)
    field_name = "default";

  if (PyString_Check(result))
    {
      const char *string = gdbpy_obj_to_string (result).release ();
      uiout->field_string (field_name, string);
      xfree ( (void *)string);
    }
  else if (PyList_Check (result))
    {
      PyObject *item;
      Py_ssize_t i = 0;
      struct cleanup *cleanups = make_cleanup_ui_out_list_begin_end (uiout, field_name);
      for(i = 0; i < PyList_GET_SIZE (result); ++i)
	{
	  struct cleanup *cleanup_item = make_cleanup_ui_out_tuple_begin_end (uiout, NULL);
	  item = PyList_GetItem (result, i);
	  parse_mi_result (item, NULL);
	  do_cleanups (cleanup_item);
	}
      do_cleanups (cleanups);
    }
  else if ( PyDict_Check (result))
    {
      PyObject *key, *value;
      Py_ssize_t pos = 0;
      while ( PyDict_Next (result, &pos, &key, &value) )
	{
	  char *key_string = gdbpy_obj_to_string (key).release ();
	  parse_mi_result (value, key_string);
	  xfree ( (void *) key_string);
	}
    }
}

/* Called from mi_command_py's invoke to invoke the command.  */

void
py_mi_invoke (void *py_obj, char **argv, int argc)
{
  micmdpy_object *obj = (micmdpy_object *) py_obj;
  PyObject *argobj, *result,  **strings;
  int i;

  gdbpy_enter enter_py (get_current_arch (), current_language);

  if (! obj)
    error(_("Invalid invocation of Python micommand object."));

  if (! PyObject_HasAttr ((PyObject *) obj, invoke_cst))
    {
      error (_("Python command object missing 'invoke' method."));
    }

  strings = (PyObject **) malloc (sizeof(PyObject *) * argc);
  argobj = PyList_New (argc);
  if ( !argobj)
    {
      gdbpy_print_stack ();
      error (_("Failed to create the python arguments list."));
    }

  for (i = 0; i < argc; ++i)
    {
      strings[i] = PyUnicode_Decode (argv[i], strlen(argv[i]), host_charset (), NULL);
      if (PyList_SetItem (argobj, i, strings[i]) != 0)
	{
	  error (_("Failed to create the python arguments list."));
	}
    }

  result = PyObject_CallMethodObjArgs ((PyObject *) obj, invoke_cst, argobj,
				       NULL);

  if (result)
    {
      parse_mi_result (result, NULL);
      Py_DECREF (result);
    }

  Py_DECREF (argobj);
  for (i = 0; i < argc; ++i)
    {
      Py_DECREF (strings[i]);
    }
  free (strings);
}

/* Parse the name of the MI command to register.

   This function returns the xmalloc()d name of the new command. On error
   sets the Python error and returns NULL.  */

static char *
micmdpy_parse_command_name (const char *name)
{
  int len = strlen (name);
  int i, lastchar;
  char *result;

  /* Skip trailing whitespaces. */
  for (i = len - 1; i >= 0 && (name[i] == ' ' || name[i] == '\t'); --i)
    ;
  if (i < 0)
    {
      PyErr_SetString (PyExc_RuntimeError, _("No command name found."));
      return NULL;
    }
  lastchar = i;

  /* Skip preceding whitespaces. */
  /* Find first character of the final word.  */
   for (; i > 0 && (isalnum (name[i - 1])
 		   || name[i - 1] == '-'
 		   || name[i - 1] == '_');
        --i)
     ;
   /* Skip the first dash to have to command name only.
    * i.e. -thread-info -> thread-info
    */
   if(name[i] == '-' && i < len - 2)
     i++;

   if( i == lastchar)
    {
      PyErr_SetString (PyExc_RuntimeError, _("No command name found."));
      return NULL;
    }

  result = (char *) xmalloc (lastchar - i + 2);
  memcpy(result, &name[i], lastchar - i + 1);
  result[lastchar - i + 1] = '\0';

  return result;
}

/* Object initializer; sets up gdb-side structures for MI command.

   Use: __init__(NAME).

   NAME is the name of the MI command to register. It should starts with a dash
   as a traditional MI command does.  */

static int
micmdpy_init (PyObject *self, PyObject *args, PyObject *kw)
{
  micmdpy_object *obj = (micmdpy_object *) self;
  //static char *keywords[] = { "name", NULL };
  const char *name;
  char *cmd_name;
  struct mi_cmd *cmd = NULL;

  if(! PyArg_ParseTuple (args, "s", &name))
    return -1;
  
  cmd_name = micmdpy_parse_command_name (name);
  if (! cmd_name)
    return -1;

  Py_INCREF (self);

  TRY
  {
    mi_command *micommand = new mi_command_py (cmd_name, NULL, (void *) self);

    bool result = insert_mi_cmd_entry (mi_cmd_up (micommand));

    if (! result)
      {
	PyErr_Format (PyExc_RuntimeError,
		      _("Unable to insert command. The name might already be in use."));
	return -1;
      }
  }
  CATCH (except, RETURN_MASK_ALL)
  {
    xfree (cmd_name);
    Py_DECREF (self);
    PyErr_Format (except.reason == RETURN_QUIT
		    ? PyExc_KeyboardInterrupt : PyExc_RuntimeError,
		    "%s", except.message);
    return -1;
  }
  END_CATCH

  xfree (cmd_name);
  return 0;
}

/* Initialize the MI command object.  */

int
gdbpy_initialize_micommands(void)
{
  micmdpy_object_type.tp_new = PyType_GenericNew;
  if (PyType_Ready (&micmdpy_object_type) < 0)
    return -1;

  if (gdb_pymodule_addobject (gdb_module, "MICommand",
  			      (PyObject *) &micmdpy_object_type) < 0)
      return -1;

  invoke_cst = PyString_FromString("invoke");
  if (invoke_cst == NULL)
    return -1;
  
  return 0;
}

static PyMethodDef micmdpy_object_methods[] =
    {
	{ 0 }
    };

PyTypeObject micmdpy_object_type =
{
  PyVarObject_HEAD_INIT (NULL, 0)
  "gdb.MICommand",		  /*tp_name*/
  sizeof (micmdpy_object),	  /*tp_basicsize*/
  0,				  /*tp_itemsize*/
  0,				  /*tp_dealloc*/
  0,				  /*tp_print*/
  0,				  /*tp_getattr*/
  0,				  /*tp_setattr*/
  0,				  /*tp_compare*/
  0,				  /*tp_repr*/
  0,				  /*tp_as_number*/
  0,				  /*tp_as_sequence*/
  0,				  /*tp_as_mapping*/
  0,				  /*tp_hash */
  0,				  /*tp_call*/
  0,				  /*tp_str*/
  0,				  /*tp_getattro*/
  0,				  /*tp_setattro*/
  0,				  /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
  "GDB mi-command object",		  /* tp_doc */
  0,				  /* tp_traverse */
  0,				  /* tp_clear */
  0,				  /* tp_richcompare */
  0,				  /* tp_weaklistoffset */
  0,				  /* tp_iter */
  0,				  /* tp_iternext */
  micmdpy_object_methods,	  /* tp_methods */
  0,				  /* tp_members */
  0,				  /* tp_getset */
  0,				  /* tp_base */
  0,				  /* tp_dict */
  0,				  /* tp_descr_get */
  0,				  /* tp_descr_set */
  0,				  /* tp_dictoffset */
  micmdpy_init,			  /* tp_init */
  0,				  /* tp_alloc */
};
