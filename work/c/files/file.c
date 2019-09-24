#include <stdio.h>
#define STR_SIZE 100
#define FILE_SIZE 10000

typedef enum
{
	OPEN=1,
	READ,
	WRITE,
	CLOSE
}MenuCase;

int main()
{
	char newString[STR_SIZE];
	char fileString[FILE_SIZE];
	char ch;
	int option;
	int i;
	FILE *file = NULL;

	puts("****************FILES******************");
	puts("Options:");
	puts("	1:Open");
	puts("	2:Read");
	puts("	3:Write");
	puts("	4:Close");
	puts("****************FILES******************");
	while(CLOSE!=option)
	{
	puts("Insert option\n");
	scanf("%d",&option);
	getchar();
		switch(option)

		{
			case OPEN:
				puts("Insert the full name of the file");
				gets(newString);	
				file = fopen(newString,"a+");
				if(NULL == file)
				{
					puts("Can't open file");
				}
				break;

			case READ:
				
				if(NULL != file)
				{
					rewind(file);
					while(fgets(fileString,FILE_SIZE,file))
					{
						printf("%s\n", fileString);			
					}
				}
				else
				{
					puts("No file to read from");
				}

				break;

			case WRITE:
				if(NULL != file)
				{
					puts("Insert what you want to write:");
					gets(fileString);
					fprintf(file,"%s\n",fileString);
				}
				else
				{
					puts("No file to write to");
				}
				
				break;

			case CLOSE:
				fclose(file);
				break;
			
		}	
	}
}


