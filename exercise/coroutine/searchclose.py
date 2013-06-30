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
        try:
            while True:
                line = (yield)
                if pattern in line:
                    print(line)
        except GeneratorExit:
            print('genertor closed')

p = search('python')
p.send('python 3')
p.close()


