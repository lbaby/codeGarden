#/usr/bin/env python
import random

def insertion_sort(a):
	'''
	Demostration for insert algorithm
	a is the list to be sorted
	'''

	i=1
	while i < len(a):
		key=a[i]
		j = int(i -1)
		while j >= 0 and a[j] > key:
			a[j+1] = a[j]
			print ' a[' , j ,']->a[',  j+1,']'
			print a
			j = j-1
		a[j+1] = key
		print 'key -> a[' , j+1, ']'
		print a
		i = i+1
	return a

if __name__ == '__main__':
	a=[]
	b=list()
	for  i in range(1000):
		b.append(i)
	for i in range(5):
		#choose 5  random numbers in (1...1000) as a sort list
		a.append( random.choice(b))
	print a
	insertion_sort(a)
	print sorted(a)
	

