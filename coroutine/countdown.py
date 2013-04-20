def countdown(n):
    print('count down from {0}'.format(n))
    while n > 0 :
        yield n
        n -=  1



x=countdown(5)
print('x is set')
for i in x:
    print(i)
