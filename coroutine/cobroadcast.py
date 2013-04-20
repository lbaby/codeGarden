import functools

def coroutine(function):
    @functools.wraps(function)
    def wrapper(*args, **kwargs):
        generator = function(*args, **kwargs)
        next(generator) #prime the generator
        return generator
    return wrapper

import time
def follow(thefile, target):
    thefile.seek(0,2)      # Go to the end of the file
    while True:
        line = thefile.readline()
        if not line:
          time.sleep(0.1)    # Sleep briefly
          continue
        target.send(line)

@coroutine
def broadcast(targets):
    while True:
        item = (yield)
        for target in targets:
            target.send(item)


@coroutine
def grep(pattern,target):
    while True:
        line = (yield)           # Receive a line
        if pattern in line:
            target.send(line)


@coroutine
def printer():
    while True:
        line = (yield)
        print(line, end='')

f = open('a')
follow(f,
           broadcast([grep('python',printer()),
                      grep('ply',printer()),
            grep('swig',printer())])
           )


