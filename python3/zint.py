#!/user/bin/env python3
#-*- coding: UTF-8 -*-
import sys
class zint(int):
	'''
	zint can print integer in chinese way
	and use as a real int
	'''
	def __init__(self,other=0):
		self.number='零壹贰叁肆伍陆柒捌玖'
		self.base=('拾','佰','仟','万','拾万','佰万', '仟万','亿')
		self.invalid='invalid'

		if isinstance(other,int): #init with int
			self.i=other
		elif isinstance(other, str): #init with chinese str
			setlf.i = ztoi(other)
		else:
			raise KeyError ('unsupport init type for zint')

	def __repr__(self):
		return str(self)

	def ztoi(self,s):
		return 0


	def __int__(self):
		return self.i

	def __str__(self):
		numl=list()
		basel=list()
		left=0
		base_count=0
		n=self.i
		left=n%10
		numl.append(left)
		n /= 10
		while  int(n)>0:
			left=n%10
			numl.append(int(left))
			basel.append(base_count)
			base_count += 1
			n /= 10

		rets=''
		for x in range(len(numl)):
			if (numl[int(x)] != self.invalid ) :
				rets +=  self.number[numl[int(x)]] + '|'
			if x >= len(basel):
				break
			if (basel[int(x)] != self.invalid ) :
				rets +=  self.base[basel[x]%len(self.base)] + '|'
		for x in range(len(numl)):
			if numl[x]  == 0: #1000x000  the 0 in tail
				print(self.number[numl[int(x)]] )
				numl[x] = self.invalid
				if (x +1 ) % len(self.base): #not 亿
						print(self.base[basel[x]%len(self.base)] )
		
		numl.reverse()
		basel.reverse()
		rets=''
		for x in range(len(numl)):
			if (numl[int(x)] != self.invalid ) :
				rets +=  self.number[numl[int(x)]] + '|'
			if x >= len(basel):
				break
			if (basel[int(x)] != self.invalid ) :
				rets +=  self.base[basel[x]%len(self.base)] + '|'
				
		return rets

z=zint(int(sys.argv[1]))
print(z)
			
			

