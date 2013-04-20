
def search(pattern):
        print ('looking for {0}'.format(pattern))
        while True:
            line = (yield)
            if pattern in line:
                print(line)

p = search('python')


