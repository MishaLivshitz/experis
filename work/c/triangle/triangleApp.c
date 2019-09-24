#include <stdio.h>
#include "triangle.h"

int main(){


int size;
char charToPrint;

printf("Please insert size and a charecter you want to print\n");
scanf("%d %c",&size,&charToPrint);
printf("\n");
printTriangle(size,charToPrint);

printf("\n");
printf("Please insert size and a charecter you want to print\n");
scanf("%d %c",&size,&charToPrint);
printf("\n");
printTriangleReversed(size, charToPrint);

printf("\n");
printf("Please insert size and a charecter you want to print\n");
scanf("%d %c",&size,&charToPrint);
printf("\n");
printTriangleFull(size, charToPrint);

printf("\n");
printf("Please insert size and a charecter you want to print\n");
scanf("%d %c",&size,&charToPrint);
printf("\n");
printTriangleWithSpaces(size, charToPrint);

printf("\n");
printf("Please insert size and a charecter you want to print\n");
scanf("%d %c",&size,&charToPrint);
printf("\n");
printTriangleWithSpacesReversed(size, charToPrint);

printf("\n");
printf("Please insert size and a charecter you want to print\n");
scanf("%d %c",&size,&charToPrint);
printf("\n");
printDiamond(size,charToPrint);


return 0;
}
