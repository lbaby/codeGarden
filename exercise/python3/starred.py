def muti(a,b,c):
    return a*b*c

a=(3,4,5)
print(muti(*a)) #muti(3,4,5)
print(muti(a))#syntax error:require 3 args ,but only one supplied
