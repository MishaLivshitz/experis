#include <stdio.h>
#include "sort.h"
#define TRUE 1
#define FALSE 0

void swap(int *a, int *b){

	int temp = *a;
	*a=*b;
	*b=temp;
}

int checkParams(int *arr, int size){

	if(arr==NULL){
		return NULL_POINTER_ERR;		
	}

	if(size==0){
		return ZERO_SIZE;		
	}

	return STATUS_SUCCESS;
}

int checkOneZeroPramas(int *arr, int size){

	int i;
	if(!checkParams(arr, size)){
			for(i=0;i<size;i++){
				if(arr[i]!=0&&arr[i]!=1){
					return NON_VALID_VALUE;					
					}
				}
		}
	return STATUS_SUCCESS;
}

int printArray(int *arr, int size){

	int i,check;

	if(check = (checkParams(arr,size))!=STATUS_SUCCESS){
		return check;
		}
	
	for (i=0;i<size;i++){
		printf("%d ",arr[i]);
	}
	return STATUS_SUCCESS;
}

int BubbleUp(int *arr, int size)
{
	int j,isSwaped=FALSE;

	for(j=0;j<size-1;j++){
			if(arr[j]>arr[j+1]){
				swap(&arr[j],&arr[j+1]);
				isSwaped=TRUE;
				}	
			}
	return isSwaped;
}

int BubbleDown(int *arr, int size, int currIndex)
{
 int k;

	for(k=currIndex;k<size,size&&arr[k]%2!=0;k++);
			
			while(k>currIndex && k<size){
				swap(&arr[k],&arr[k-1]);
				k--;
			}
}
/*

for each odd value
	bubbleDown even value


*/
int bubbleSort(int *arr,int size){

	int i,check;

	if(check = (checkParams(arr,size))!=STATUS_SUCCESS){
		return check;
		}
	
	for(i=0;i<size;i++){
		if(FALSE==BubbleUp(arr,size-i))
			{
			 	break;
			}
		}
	return STATUS_SUCCESS;
}

int oddEvenSort(int *arr, int size){
	int i,j,check;

	if(check = (checkParams(arr,size))!=STATUS_SUCCESS){
		return check;
		}

	for(i=0; i<size ;i++){
			BubbleDown(arr,size,i);
		}

	return STATUS_SUCCESS;
}

int oneZeroSort(int *arr, int size){


int i,j,check;

	if(check = (checkOneZeroPramas(arr,size))!=STATUS_SUCCESS){
		return check;
		}
	oddEvenSort(arr,size);
	return STATUS_SUCCESS;
}
