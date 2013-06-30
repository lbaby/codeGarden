def foo (n):
	class acc:
		def __init__ (self, s):
			self.s = s
		def inc (self, i):
			self.s += i
			return self.s
	return acc (n).inc

a=foo(4)
a(5)
