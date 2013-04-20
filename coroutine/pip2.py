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
loglines=follow(logfile)


def search(pattern,  lines):
    for line in lines:
        if pattern in line:
            yield line

pylines = search('python', loglines)
for pyline in pylines:
    print("{0}".format(pyline),end="")

