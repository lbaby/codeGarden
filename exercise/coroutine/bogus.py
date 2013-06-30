def countdown(n):
        print("Counting down from {0}".format( n))
        while n >= 0:
            newvalue = (yield n)
            # If a new value got sent in, reset n with it
            if newvalue is not None:
                n = newvalue
            else:
                n -= 1


c = countdown(5)
for n in c:
    print(n)
    if n == 5:
        c.send(3)

