import time
def follow(file):
    file.seek(0,2)
    while True:
        line = file.readline()
        if not line:
            time.sleep(0.1)
            continue
        yield line

logfile=open('a')

for line in follow(logfile):
    print("{0}".format(line),end="")
