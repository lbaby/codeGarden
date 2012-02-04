#include <stdio.h>
int main(void)
{
    int i = 0;
    /* firstly, capture the input */
    scanf("%d", &i);
    /* secondly , extract for each number:
       1234 -> 4,3,2,1
    */
    int ia[256] = {0};
    int len = 0;
    while(i){
        ia[len++] = i%10;
        i /= 10;
    }
     /* thirdly, reverse the array */
     int j = 0;
     while(j < len-j-1){
         int t = ia[j];
         ia[j] = ia[len-j-1];
         ia[len-j-1] = t;
         j++;
     }
     /*let's see if it works */
     for (j=0; j < len; j++){
        printf("%d ", ia[j]);
        }
     putchar('\n');
     return 0;
}


