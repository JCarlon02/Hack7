#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "array_utils.h"

int contains(const int *arr, int size, int x) {
  int i;
  if(arr == NULL){
    return 1;
  }
  if (size < 0){
    return 1;
  }
  for (i = 0; i < size; i++) {
    if (arr[i] == x) {
      return 1;
    }
    }
    return 0;
  }

int containsWithin(const int *arr, int size, int x, int i, int j) {
  int n;
  if(arr == NULL){
    return 1;
  }
  if (size < 0){
    return 1;
  }
  for (n = i; n <= j; n++) {
    if (arr[n] == x) {
      return 1;
    }
  }
  return 0;
}

int *paddedCopy(const int *arr, int oldSize, int newSize) {
  int *copy = (int *)malloc(sizeof(int) * newSize);
  int i;
  if(arr == NULL){
    return 0;
  }
  if (oldSize < 0){
    return 0;
  }
  for (i = 0; i < newSize; i++) {
    if (i >= oldSize) {
      copy[i] = 0;
    } else {
      copy[i] = arr[i];
    }
  }

  return copy;
}

void reverse(int *arr, int size) {
  int j = size;
  int t;
  for (int i = 0; i < size / 2; i++) {
    t = arr[i];
    arr[i] = arr[size - 1 - i];
    arr[size - 1 - i] = t;
    j--;
  }
}

int *reverseCopy(const int *arr, int size) {
  int *resCopy = paddedCopy(arr, size, size);
  reverse(resCopy, size);

  return resCopy;
}
