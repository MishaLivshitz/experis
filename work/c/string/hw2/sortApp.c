#include <stdio.h>
#include "sort.h"
#define SIZE 10


int main(){

int arr[SIZE]={1,6,2,-4,8,3,-15,-4,5,12};

int arr1[SIZE]={1,0,0,1,1,0,1,0,0,1};

printf("Before bubbleSort:\n");
printArray(arr, SIZE);
printf("\n");
bubbleSort(arr,SIZE);
printf("After bubbleSort:\n");
printArray(arr, SIZE);

printf("\n");
printf("Before oddEvenSort:\n");
printArray(arr, SIZE);
printf("\n");
oddEvenSort(arr,SIZE);
printf("After oddEvenSort:\n");
printArray(arr, SIZE);
printf("\n");

printf("Before oneZeroSort:\n");
printArray(arr1, SIZE);
printf("\n");
oneZeroSort(arr1,SIZE);
printf("After oneZeroSort:\n");
printArray(arr1, SIZE);
printf("\n");



return 0;
}
