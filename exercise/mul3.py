#! /usr/bin/env python
#vim:ts=4 sw=4 ai expandtab noet nowrap ft=py fdm=syntqax:
'''
Find the max one of n consecutive multiply  result out of MxM matrix.
consecutive means :landscape vertical or diagonal
'''

#     /
#   + -- 
#   | \
def gr(x, y,n):
    ur = []
    r = [] 
    rd=[]
    d = []
    for  i in range(n):
        ur.append((x-i , y+i,))
        r.append((x, y+i,))
        rd.append((x+i, y+i,))
        d.append((x+i, y,))
    yield ur  #up right
    yield r   #right 
    yield rd  #lower right
    yield d   #down

def allNCombination(a,n):
    validCoordinate =  lambda  xy : xy < len(a) and xy >=0 
    validRange =  lambda  r : len(filter (validCoordinate, r)) == 2
    value = lambda p: a[p[0]][p[1]]
    for y in range(len(a)):
       for x in range(len(a[y])): 
          for r in gr(x, y, n): #Let's start from this point
             if len(filter(validRange, r)) == n:#Get a valid n point
                 yield map(value,r)  #return the value

def whichRange(a2d, n,  rule, op ):
    return rule( map(op,  allNCombination(a2d, n) ))

M=10
nn=3
#For test random 2d array
import random
c =  [ [ int(random.random() * 1031 * random.choice([-1,1])) 
    for x in range(M)] 
    for y in range(M) ] 

#pretty print
for line in c:
    for row in line:
       print row,'\t',
    print
    
op = lambda s:[reduce (lambda x,y: x*y,  s, 1),s]
rule = lambda x:max(x , key= lambda k:k[0])

print whichRange(c, 3 , rule, op)

