import functools

def coroutine(function):
    @functools.wraps(function)
    def wrapper(*args, **kwargs):
        generator = function(*args, **kwargs)
        next(generator) #prime the generator
        return generator
    return wrapper

@coroutine
def search(pattern):
        print ('looking for {0}'.format(pattern))
        while True:
            line = (yield)
            if pattern in line:
                print(line)

#p = search('python')


