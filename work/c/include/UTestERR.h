#ifndef __UTEST_ERR_H_
#define __UTEST_ERR_H_
#define BIG_ALLOCATION_SIZE 1000000000000000
#define RESET "\033[0m"
#define KGRN  "\x1B[32m"
#define KRED  "\x1B[31m"

typedef enum
{
	TEST_SUCCESS = TRUE,
	TEST_FAILED = FALSE
}UTestERR;

#endif
