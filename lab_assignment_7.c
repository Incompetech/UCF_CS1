#include <stdio.h>

void bubble_sort(int arr[], int n, int swaps[]) {
  int i, j, temp;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
        swaps[i]++;
      }
    }
  }
}

int main() {
  int arr[] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
  int n = sizeof(arr) / sizeof(arr[0]);
  int swaps[n];
  for (int i = 0; i < n; i++) {
    swaps[i] = 0;
  }

  bubble_sort(arr, n, swaps);

  printf("Index\tSwaps\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%d\n", i, swaps[i]);
  }
  return 0;
}
