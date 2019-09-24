#include<stdio.h>
#include <stdlib.h>

#define MAX(x,y) (x)>(y)?(x):(y)



int main(int argc,char* argv[])
{
	int a=atoi(argv[1]);
	int b=atoi(argv[2]);
	int i;	

	for(i=1;i<argc;i++)
	{
		printf("%d ",atoi(argv[i]));
	}

	printf("\nMax(%d,%d)=%d\n",a,b,MAX(a,b));
}
