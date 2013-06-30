class GrepHandler(object):
        def __init__(self,pattern, target):
            self.pattern = pattern
            self.target = target
        def send(self,line):
            if self.pattern in line:
                self.target.send(line)

