#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG
#endif

#pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic ignored "-Wpedantic"

#ifdef DEBUG
    #define assert(X) (X)?0:(fprintf(stderr,\
			"Assertion failed ("#X") in file " __FILE__                                            \
            " on line %d, created on " __DATE__\
            "...", __LINE__), abort(),1)
#else
    #define assert(X) (0)
#endif


#define PASTE(X,Y)  X ## _ ## Y


void Hash_Map(char *str)
{
    printf("Hash_Map got '%s'\n", str);
}

#ifndef COND
#define COND 100
#endif


int main(int argc, char* argv[], char* argp[])
{

#ifndef COND
	printf("COND not defined\n");
#else
	#if COND > 10
		printf("COND defined to %d\n", COND);
	#else
		#error "COND should be greater than 10"
	#endif
#endif


	printf("In file %s in functions %s @Line %d, on day %s at time %s\n",
		__FILE__, __FUNCTION__, __LINE__, __DATE__, __TIME__);
	printf("STDC %d\n", __STDC__);
#ifdef __STDC_VERSION__
	printf("STDC Version %lu\n", __STDC_VERSION__);
#endif




#define PRINT_NAME(X)	printf(#X "= %s\n", X)
#define PRINT_VAL(X)	printf(#X "= %d\n", X)

	PRINT_NAME(__FILE__);
	PRINT_VAL(__LINE__);
	PRINT_NAME(__FUNCTION__);
	PRINT_NAME(__DATE__);
	PRINT_NAME(__TIME__);

    PASTE(Hash, Map)("Hello World!");

	assert(COND>10);
	assert(COND<10);

    return 0;

}

