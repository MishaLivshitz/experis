
#define STATUS_SUCCESS 0
#define NULL_POINTER_ERR 1
#define ZERO_SIZE 2
#define NON_VALID_VALUE 3


/*Author:Michael Livshitz
  Date:28/03/19*/

/*Sort the array
 Input: 
	arr: pointer to array
	size: the size of the array
 Output: sorted array
*/
int bubbleSort(int *arr,int size);
/*
 Input: 
	arr: pointer to array
	size: the size of the array
	
 Output:
	Sorted array that the odd numbers appers from left and even numbers from right
*/
int oddEvenSort(int *arr, int size);
/*
 Input: 
	arr: pointer to array which contains '0's and '1's
	size: the size of the array
	
 Output:
	Sorted array that the '0's appers from left and '1's from right
*/
int oneZeroSort(int *arr, int size);

/*
 Input: 
	arr: pointer to array which contains '0's and '1's
	size: the size of the array
	
 Output:
	prints the array
*/
int printArray(int *arr, int size);
