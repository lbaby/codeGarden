def get_function(module, function_name):
    function = get_function.cache.get((module, function_name), None) 
    if function is None:
        try:
            function = getattr(module, function_name)
            if not hasattr(function, "__call__"):
                raise AttributeError() 
                get_function.cache[module, function_name] = function
        except AttributeError:
                function = None
        return function

get_function.cache = {}

import re
print(get_function(re, 'compile'))


def foo():
    print(__name__)

foo.bar = 'Hello world'

foo()
foo.bar
