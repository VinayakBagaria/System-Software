#include <stdio.h>
#include<string.h>
#include<stdlib.h>
 
int main(void)
{
    long int x = 0x3F01;
    long int y = 0x239A;
    long int sum;
 	
 	sum = x + y;
 
    printf("\n%lX",sum);
    
    char str1[10]="3F01";
	x=atoi(str1);
    char str2[10]="239A";
	y=atoi(str2);
	sum=x+y;
 
    printf("\n%x",sum);
 
    return 0;
}
