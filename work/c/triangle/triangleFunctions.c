#include <stdio.h>

int printTriangle(int size,char charToPrint){
	
	int i,j;
	for(i=0;i<=size;i++){
	   for(j=0;j<i;j++)
		{
		  printf("%c",charToPrint);
		}
	   printf("\n");
	}
	return 1;
}


int printTriangleReversed(int size,char charToPrint){
	
	int i,j;
	for(i=size;i>0;i--){
	   for(j=0;j<i;j++)
		{
		  printf("%c",charToPrint);
		}
	   printf("\n");
	}
	return 1;
}

int printTriangleFull(int size,char charToPrint){

	printTriangle(size,charToPrint);
	printTriangleReversed(size-1,charToPrint);
	return 1;
}
int printTriangleWithSpaces(int size, char charToPrint){

	int i,j,k,iteration=1;
	
	for(i=size;i>0;i--,iteration++){
	   for(j=1;j%i!=0;j++)/*This loop prints spaces until it founds the first place for the character*/
		{
			printf(" ");
		}
	   
	   for(k=0;k<iteration;k++){ 
			printf("%c ",charToPrint);
			}
 	printf("\n");
	}
}

int printTriangleWithSpacesReversed(int size,char charToPrint){
	int i,j,k,iteration=0;
	
	for(i=0;i<size;i++,iteration++){
	   for(j=0;j<iteration;j++)
		{
			printf(" ");
		}
	   
	   for(k=0;k<size-iteration;k++){
			printf("%c ",charToPrint);
			}
 	printf("\n");
	}
return 1;
}

int printDiamond(int size,char charToPrint){
	int i,j,k,iteration=0;
	printTriangleWithSpaces(size,charToPrint);

	for(i=0;i<size-1;i++,iteration++){
		printf(" ");
	   for(j=0;j<iteration;j++)
		{
			printf(" ");
		}
	   
	   for(k=0;k<size-1-iteration;k++){
			printf("%c ",charToPrint);
			}
 	printf("\n");
	}
}

