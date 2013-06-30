# cothread.py
#
# A thread object that runs a coroutine inside it.  Messages get sent
# via a queue object

from threading import Thread
import queue
from coroutine import *

@coroutine
def threaded(target):
    messages = queue.Queue()
    def run_target():
        while True:
            item = messages.get()
            if item is GeneratorExit:
                target.close()
                return
            else:
                target.send(item)
    Thread(target=run_target).start()
    try:
        while True:
            item = (yield)
            messages.put(item)
    except GeneratorExit:
        messages.put(GeneratorExit)

# Example use

if __name__ == '__main__':
    import xml.sax
    from cosax import EventHandler
    from buses import *

    xml.sax.parse("/Users/ly/ws/allroutes.xml", EventHandler(
                    buses_to_dicts(
                    threaded(
                         filter_on_field("route","22",
                         filter_on_field("direction","North Bound",
                         bus_locations()))
                    ))))
                 
