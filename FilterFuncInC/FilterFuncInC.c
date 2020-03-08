#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5

struct Array { void *ptr; int length; };
typedef struct Array Array;

void freeArray(Array *array)
{
    free(array->ptr);
    free(array);
}

Array *filter(int filterFunc(void*), void *array, size_t length, size_t sizeOfElement)
{
    int numberOfTrues = 0;
    char *arrayp = (char *) array;
    int booleans[length];
    memset(booleans, 0, sizeof(int) * length);

    // Apply predicate function over the array and store the results
    for (size_t i = 0; i < length; i++)
    {
        booleans[i] = filterFunc(arrayp + i * sizeOfElement);
        if (booleans[i]) numberOfTrues++;
    }
    
    char *filteredArray = (char *) malloc(sizeOfElement * numberOfTrues);
    int offsetForFilteredArray = 0, offsetForOriginalArray;

    for (size_t i = 0; i < length; i++)
    {
        if (booleans[i])
        { // Copy the elements that returned true from the predicate function
            memcpy(filteredArray + offsetForFilteredArray, arrayp + i * sizeOfElement, sizeOfElement);
            offsetForFilteredArray += sizeOfElement;
        }
    }

    Array *finalArray = (Array *) malloc(sizeof(Array));
    finalArray->length = numberOfTrues;
    finalArray->ptr = filteredArray;
    return finalArray;
}

int greaterThan4(void *element)
{
    int *elementp = (int *) element;
    return *elementp > 4;
}

void printArray(int *array, int length)
{
    if (length > 0) printf("%d", array[0]);

    for (size_t i = 1; i < length; i++) printf(" %d", array[i]);
    puts("");
}

int main()
{
    int array[SIZE] = { 2, 5, 3, 0, 6 };
    Array *filteredArray = filter(greaterThan4, array, SIZE, sizeof(int));

    printf("Before filter: ");
    printArray(array, SIZE);

    printf("After filter: ");
    printArray(filteredArray->ptr, filteredArray->length);
    freeArray(filteredArray);

    return EXIT_SUCCESS;
}
