



class cir(object):
	def __init__(self,radius):
		self.radius=radius
	def __str__(self):
		return 'this {0}'.format(self.radius())
	def plus(self ):
		return self.radius *1
	@property
	def radius(self):
		return self.__radius

	@radius.setter
	def radius(self,radius):
		assert radius > 0,'must  greater than 0'
		self.__radius=radius
a=cir(2)
print(a.radius)
a.radius=-2
print(a.radius)
