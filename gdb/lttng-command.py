#! /usr/bin/python

import gdb
import subprocess
import re
import babeltrace

class LTTngCommand (gdb.Command):
    
    filename = '/home/didier/lttng-traces/benchmark-gdb-i10000-o100000-s1-e8-20160412-160353' 
    babel_reader = None
    events = None

    def __init__ (self):
        super (LTTngCommand, self).__init__("lttng", gdb.COMMAND_USER)

    def invoke (self, arg, from_tty):

        if "start" in arg:
            print("Starting tracing")
            out1 = subprocess.check_output ("lttng create gdb-tracing", shell=True)
            match = re.search ('(/home/.*)\n', out1.decode ())
            if match:
                print (match.group (1))
                self.filename = match.group (1)
            #print ("Starting in : " + out1)
            out2 = subprocess.check_output ("lttng add-context -u --type=vtid", shell=True) 
            out3 = subprocess.check_output ("lttng enable-event -u gdb_trace:*", shell=True) 
            #print ("Output is : " + out2)
            out4 = subprocess.check_output ("lttng start", shell=True)
            #print ("start " + out3)

        elif "install" in arg:
            gdb.execute("tstart")

        elif "stop" in arg:
            print("Stopping tracing")
            p1 = subprocess.Popen ("lttng stop", shell=True)
            p1.wait ()
            p2 = subprocess.Popen ("lttng destroy", shell=True)
            p2.wait ()
            print (self.filename)

        elif "view" in arg:
            if not self.babel_reader:
                self.babel_reader = babeltrace.TraceCollection ()
                self.babel_reader.add_trace (self.filename + "/ust/uid/1000/64-bit/", 'ctf')
                self.events = self.babel_reader.events
            ev = self.events.__next__()
            print("Data collected at tracepoint " + str(ev['tp_id']) + " on thread " + str(ev['vtid']) + " and trace frame " + str(ev['traceframe_id']) + ":")
            print("x = " + str(ev['x']))
            print("y = " + str(ev['y']))
            #print(','.join(ev.keys())) #ev['tp_id'] + " frame " + ev['traceframe_id'] + " at " + ev['timestamp_begin'])
         


LTTngCommand ()
