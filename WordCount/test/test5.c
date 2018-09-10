#include<stdio.h>
void main()
{
    //test
    int x, y;
    int a, b, c;
    a=x/100;
    b=x/10%10;
    c=x%10;
    printf("Please input a num:");
    scanf("%d",&x);
    y=a+10*b+100*c;
    printf("y=%d\n",y);
}
