#include <stdio.h>

int   next[128];   
  void   Get_Next(char   *p)   
  {     
  for   (   int   w=0;   w<128;   w++)   
  next[w]   =   0xefffffff;     
  int   i   =   0,   j   =   -1;     
  next[0]   =   -1;   
  int   plen   =   strlen(p);     
  while   (i   <   plen)     
  {       
  if   (   j==-1   ||   p[i]   ==   p[j]   )     
  {     
  i++;   j++;     
  next[i]   =   j;   
  }       
  else     
  j   =   next[j];   
  }   
  }   
    
  int   Index_KMP(char   *s,   char   *p,   int   pos)   
  {     
  int   i,   j;     
  int   slen   =   strlen(s);     
  int   plen   =   strlen(p);   
  i   =   pos;   j   =   -1;     
  while   (   i<slen   &&   j<plen   )     
  {       
  if   (   j==-1   ||   s[i]   ==   p[j]   )         
  {         
  i++;           
  j++;         
  }       
  else       
  {         
  j   =   next[j];       
  }     
  }     
  if   (   j>=plen   )     
  return   i-plen;     
  else     
  return   -1;   
  }   
    
  int   main(void)   
  {     
  char   strS[]   =   "aabcab";   char   strP[]   =   "ca";   
  Get_Next(strP);   
  int   nPos   =   Index_KMP(strS,   strP,   0);     
  printf("%s" , strS+nPos); 
  return   0;   
  }   

