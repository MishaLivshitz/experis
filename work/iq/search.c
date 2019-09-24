#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

void initArr(int** arr, int size)
{
    int i,j;
    int num = 1;

    for(i=0;i<size;++i)
    {
        for(j=0;j<size;++j)
        {
            arr[i][j] = num;
            ++num;
        }
    }
}


int** create(int size)
{
    int i;
    int** arr = (int**)malloc(sizeof(int*)*size);

    if(arr==NULL)
    {
        return NULL;
    }

    for(i=0;i<size;++i)
    {
        arr[i] = (int*)malloc(sizeof(int) * size);

        if(arr[i] == NULL)
        {
            while(i>=0)
            {
                free(arr[i]);
                --i;
            }
            free(arr);

            return NULL;
        }
    }

    initArr(arr,size);
    return arr;
}

int search(int** arr , int size, int num)
{
    int i = size - 1;
    int j = 0;
    int isFound = 0;

    while(i>=0 && j<size && !isFound)
    {
        if(arr[i][j] == num)
        {
            isFound = 1;
        }
        else if( arr[i][j] < num)
        {
            ++j;
        }
        else
        {
            --i;
        }
    }

    return isFound;


}


int main()
{
    int const size = 10;
    int** arr = create(size);

    printf("isFound = %d\n", search(arr,10, 72));
    printf("isFound = %d\n", search(arr,10, 108));

    return 0;
}