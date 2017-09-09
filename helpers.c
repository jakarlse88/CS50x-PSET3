/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include <math.h>

#include "helpers.h"

#define ZERO 0

// Recursive binary search function prototype //
bool binsearch_r(int target, int array[], int min, int max);

// Simple swapping function
void swap(int *a, int *b);

/**
 * Returns true if value is in array of n values, else false.
 */

bool search(int value, int values[], int n)
{
    return (binsearch_r(value, values, ZERO, n - 1));
}


/**
 * Sorts array of n values
 */
void sort(int values[], int n) {
    // defining sorted side of array
    for (int i = 0; i < (n - 1); i++) {

    // find smallest element in unsorted side
    int min = i;
        for (int j = (i + 1); j < (n - 1); j++) {
            if (values[j] < values[min]) {
                min = j;
            }
        }
        swap(&values[min], &values[i]);
    }
}

/**
 * Recursive binary search to find int target in sorted array
 */
bool binsearch_r(int target, int array[], int min, int max){

    if (min > max) {
        return false;
    }

    int mid = (int) floor(((max - min) / 2) + min);

    if (array[mid] == target) {
        return true;
    }
    if (array[mid] > target) {
        return binsearch_r(target, array, min, mid - 1);
    } else {
        return binsearch_r(target, array, mid + 1, max);
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}