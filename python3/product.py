def product(*args):
    result = 1
    print (args,len(args),type(args))
    for arg in args:
        result *= arg
    return result

a=(3,4,5)
[*b]=a




print(product(*b))
