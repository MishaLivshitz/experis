#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define ON_64BITS (sizeof(int*) == 8)

/*gcc stack_frame.c -o sFrame*/
/*gcc stack_frame.c -m32 -o sFrame_32*/

void foo_64_2(long _a,long _b,long _c,long _d,long _e,long _f,long _g, void* _retAdd)
{
	volatile intptr_t * sp = (intptr_t *)&_g;
	
	--sp;
	*sp = *(intptr_t*)_retAdd;
	
}

void foo_64_1(long _a,long _b,long _c,long _d,long _e,long _f,long _g)
{
	volatile intptr_t * sp = (intptr_t *)&_g;
	
	--sp;	
	foo_64_2(_a,_b,_c,_d,_e,_f,7,(void*)sp);
	puts("Unreachable code\n");
	
}

void foo_32_2(long _a, void* _retAdd)
{
	volatile intptr_t * sp = (intptr_t *)&_a;
	
	--sp;
	*sp = *(intptr_t*)_retAdd;
	
}

void foo_32_1(long _a)
{
	
	volatile intptr_t * sp = (intptr_t *)&_a;
	
	--sp;
	foo_32_2(1,(void*)sp);
	puts("Unreachable code\n");

}

int main()
{
	int i = 1;
	
	if(ON_64BITS)
	{
		foo_64_1(1,2,3,4,5,6,7);		
	}
	else
	{
		 foo_32_1(1);
	}
	
	printf("Returned\n");
	
	
	return 1;
}
