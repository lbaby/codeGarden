import xml.sax
import functools

def coroutine(function):
    @functools.wraps(function)
    def wrapper(*args, **kwargs):
        generator = function(*args, **kwargs)
        next(generator) #prime the generator
        return generator
    return wrapper


class EventHandler(xml.sax.ContentHandler):
        def __init__(self,target):
            self.target = target
        def startElement(self,name,attrs):
            self.target.send(('start',(name,attrs._attrs)))
        def characters(self,text):
            self.target.send(('text',text))
        def endElement(self,name):
            self.target.send(('end',name))


@coroutine
def buses_to_dicts(target):
    while True:
        event, value = (yield)
        # Look for the start of a <bus> element
        if event == 'start' and value[0] == 'bus':
            busdict = { }
            fragments = []
            # Capture text of inner elements in a dict
            while True:
                event, value = (yield)
                if event == 'start':   fragments = []
                elif event == 'text':  fragments.append(value)
                elif event == 'end':
                    if value != 'bus':
                            busdict[value] = "".join(fragments)
                    else:
                        target.send(busdict)
                        break
@coroutine
def filter_on_field(fieldname,value,target):
     #print("looking {0}".format( value))
     while True:
        d = (yield)
        print(d)
        if d.get(fieldname) == value:
            #print("found {0}".format( value))
            target.send(d)


@coroutine
def bus_locations():
    while True:
        bus = (yield)
        print(bus)

xml.sax.parse("allroutes.xml",
                 EventHandler(
                      buses_to_dicts(
                      filter_on_field("route","147",
                      filter_on_field("direction","North Bound",
                      bus_locations())))
            ))

