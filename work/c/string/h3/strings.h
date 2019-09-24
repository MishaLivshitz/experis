#define STATUS_SUCCESS
#define NULL_POINTER_ERR
#define TRUE 1
#define FALSE 0
#define SIZE 100
/*
Author:Michael Livshitz
Date: 31/3/19
*/

/*
This function revese the string:
	EXAMPLE: abc efg => gfe cba

Output:
	if success return STATUS_SUCCES 
	else return NULL_POINTER_ERR
*/
int ReverseStr(char *str);
/*
This function squeze a given string by a given substring
	EXAMPLE: SquezeStr("Hello","lo") => "Hel"

Output:
	if success return STATUS_SUCCES 
	else return NULL_POINTER_ERR
*/
int SquezeStr(char *str, char *subStrToIgnore);
/*
This function return the binary num of a given decimal number as a string but in revesed oreder
	if you want the real binary please reverse the string
	EXAMPLE: 4 => 001

Output:
	if success return STATUS_SUCCES 
	else return NULL_POINTER_ERR
*/
char* Dec2Bin();
