#include<stdio.h>



int main()
{
	int a = 10/6*2;
	float f = 10/6*2;
	int b = (float)10/6*2;
	float g = 10.0/6*2;
	char c1 = 98;
	char c2 = 101;
	int k = (char)(c1*c2);
	int i1 = (int)c1*c2;

	void *item;
	
	
	printf("%d\n%f\n%d\n%f\n%c\n%c\n%d\n%d\n",a,f,b,g,c1,c2,k,i1);
}
