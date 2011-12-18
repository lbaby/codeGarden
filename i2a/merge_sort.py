
import random
def merge(a, left, right , end):
	''' merge two sorted sequence
	left right end of merge(Not include)
	a[left:right]
	a[right:end]
	'''
	llen=right - left
	rlen=end - right
	al=a[left:right]
	al.append(None)
	ar=a[right:end]
	ar.append(None)
	l=0
	r=0
	#print '<',left,right,end
	#print 'lr', al,ar
	#print a
	for i in range(end - left):
		if al[l] != None and ar[r] != None and (al[l] <= ar[r]):
			a[left+i] = al[l]
			l=l+1
		elif al[l] != None and ar[r] != None :
			a[left+i] = ar[r]
			r=r+1
		elif   ar[r] == None and al[l] != None:#right array is empty
			a[left+i:end] = al[l:right-left]
			break
		elif al[l] == None and ar[r] != None:
			a[left+i:end] = ar[r:end-right]
			break
	return a


def merge_sort(a,s,e):
	'''
	array
	[s:e+1]python slice [)
	'''
	if s < e:
		m=(s+e)/2 
		merge_sort(a, s, m ) #a[s:m+1]python slice [)
		merge_sort(a, m+1 , e)#a[m+1:e][m+1:e+1] python slice [)
		merge(a, s,m+1,e+1)
	return a

for x in range(10000):
	a=[]
	b=list()
	n=random.randint(100,1130)
	for  i in range(1000):
		b.append(i)
	for i in range(n):
		#choose 9  random numbers in (1...1000) as a sort list
		a.append( random.choice(b))
	b= merge_sort(a,0,n-1)
	if b!= sorted(a):
		print 'err',n, x
		print a
		print b
		print sorted(a)

#a=[0, 177, 911, 453, 566, 985]
#print merge_sort(a,0,5)
#print merge(a,0,3,6)
#print a
