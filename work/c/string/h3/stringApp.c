#include <stdio.h>
#include "strings.h"

int main()
{
 	char option,str[SIZE],subStr[SIZE],*bin;
	int exitFlag = FALSE,i;

	while(FALSE==exitFlag){
	
		puts("Options:\n");
		puts("	1: ReverseStr");
		puts("	2: SquezeStr");
		puts("	3: Dec2Bin");
		puts("	Q or q: Quit");

		puts("\nInsert your selection and press Enter:\n");
		option = getchar();
		getchar();
		switch(option){
			case '1':
			printf("Insert a sentence:");
			gets(str);
			ReverseStr(str);
			break;
			case '2':
			printf("Insert sentence and some substring:");
			gets(str);
			gets(subStr);
			puts(subStr);
			SquezeStr(str,subStr);
			break;
			case '3':
			bin=Dec2Bin();

			while(*bin!='\0')
			{
			putchar(*bin);
			bin++;
			}

			break;
			case 'q':
			case 'Q':
			exitFlag=TRUE;
			break;
			default:
			printf("Please insert ");
			}
	printf("Result: %s\n",str);
	}








return 0;
}
