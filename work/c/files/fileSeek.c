#include <stdio.h>
#define MIN_ARGS 3

typedef enum
{
	PRINT_LAST_N = 3,
	PRINT_K_TO_N = 4

}FuncActivateCase;


void PrintFileLines(FILE* _fp,size_t _fromLine, int _toLine)
{
	char nextChar;
	size_t counter=0,totalLines=0;
	while(!feof(_fp))
	{
		fscanf(_fp,"%c",&nextChar);
		nextChar == '\n' ? totalLines++:totalLines;
		if(totalLines==_toLine)
		{
			break;
		}
	}
	
	while(!feof(_fp))
	{
		fscanf(_fp,"%c",&nextChar);
		if(counter < totalLines-_toLine)
		{
			nextChar == '\n' ? counter++:counter;
		}
		else
		{
			printf("%c",nextChar);
		}
	}
}

int main(int argc,char *argv[])
{
	FILE* fp;
	size_t counter=0,totalLines=0;
	size_t n_line,k_line;
	char* fileName;
	
	if(argc < MIN_ARGS)
	{
		puts("Missing arguments (min 2)");
		return 0;
	}
	
	fileName = argv[1];

	if(NULL == (fp = fopen(fileName,"r")))
	{
		puts("File could not be opend");
	}

	switch(argc)
	{
		case PRINT_LAST_N:
			n_line = atoi(argv[2]);
			PrintFileLines(fp,n_line,-1);

		break;
		case PRINT_K_TO_N:
			n_line = atoi(argv[2]);
			k_line = atoi(argv[3]);
			PrintFileLines(fp,k_line,n_line);
		break;
	}
	
	fclose(fp);
}
