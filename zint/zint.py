#!/usr/bin/env python3
#-*- coding: UTF-8 -*-
class zint(int):
    '''
    zint can print integer in chinese way
    and use as a real int
    '''
    def __init__(self,other=0):
        self.number='零壹贰叁肆伍陆柒捌玖'
        self.base='拾佰仟万'
        self.million100='亿'
        self.million100_id=-1
        self.invalid='N/A'
        self.zhn_num={b:n for b in '拾佰仟万亿'  for n in (1e1,1e2,1e3,1e4,1e8) }
        

        if isinstance(other,int): #init with int
            self.i=other
        elif isinstance(other, str): #init with chinese str
            setlf.i = ztoi(other)
        else:
            raise KeyError ('uretsupport init type for zint')

    def __repr__(self):
        return str(self)

    def ztoi(self,s):
        i = 0
        istenheader=False
        if self.number.find(s[0] ) == -1:#so may be 拾万
           if s[0] not in zhn_num:
              if zhn_num[s[0]] == 1e1: #yes!
                  i=1e1
                  s=s[1:]
                  istenheader=True
              else:
                  raise KeyError(s , ' not a valid HAN number')

        l=len(s)
        x=0
        state_base='base'
        state_num='num'
        state=state_num
        #贰拾万|零贰仟|零壹拾亿|0贰万叁仟
        while x < l:
            if self.number.find(s[x]) != -1:
            literal_state=''

            
            
            
            
        return 0

    def __add__(self, i):
        return self.i + i
    def __muti__(self, i):
        return self.i*i


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
        
        #exract base and number
        while  int(n)>0:
            left=n%10
            numl.append(int(left))
            basel.append(base_count)
            base_count += 1
            n /= 10

        numl.reverse()
        basel.reverse()

        #adjust zero
        zero_serial=self.invalid
        first_zero_in_serial=self.invalid
        for x in range(len(numl)):
            if numl[x] == 0:
                if  zero_serial == self.invalid :
                    first_zero_in_serial=x
                    zero_serial=True
                numl[x]=self.invalid
                    
            else:
                if zero_serial != self.invalid :
                    zero_serial = self.invalid
                    numl[first_zero_in_serial] = 0

        #adjust base
        for x in range(len(basel)):
            if numl[x] == self.invalid or numl[x] == 0:
                basel[x] = [self.invalid,]
                continue
            if basel[x] >= len(self.base)  :#add 万 to 拾...to make 拾万
                y=basel[x]
                basel[x] = [basel[x]%len(self.base) ]
                if (int(y%len(self.base)) == 0 and y > len(self.base)):#
                    basel[x] += [len(self.base)-1, ]*int(y / len(self.base))

        rets=''
        #make literal string
        for x in range(len(numl)):
            if x == 0:#see if  壹拾leading and truncate to 拾
                if numl[x]==1:
                    if isinstance(basel[x],list):
                        if basel[x][0] == 0:
                           numl[x]=self.invalid
                        else:
                            if basel[x] == 0:
                               numl[x]=self.invalid
            if numl[x] != self.invalid:
                rets += '{0}'.format( self.number[numl[int(x)]] )
            if x >= len(basel):
                continue
            if not isinstance(basel[x],list) : #only  basic base
                if basel[x] != self.invalid:
                    rets +=  '{0}'.format(self.base[basel[x]])
            else: # the multiple base such as : 拾万 ,万万
                #combine 万万 ->  亿
                y=len(basel[x])-1
                while y > 0:
                    if  (basel[x][y] ==  len(self.base) -1 ) and (basel[x][y-1] == len(self.base) -1):
                        basel[x][y] = self.million100_id
                        basel[x][y-1] = self.invalid
                    y -= 1
                for y in range(len(basel[x])):
                    if basel[x][y] == self.million100_id:
                        rets +=  '{0}'.format(self.million100)
                    elif basel[x][y] == self.invalid:
                        continue 
                    else:
                        rets +=  '{0}'.format(self.base[basel[x][y]])

        return rets
if __name__ == '__main__':
    import sys
    z=zint(int(sys.argv[1]))
    z*2
    print(z)
            
            

