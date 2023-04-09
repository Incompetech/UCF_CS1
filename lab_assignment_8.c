#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapify(int arr[], int n, int i) {
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;

  if (l < n && arr[l] > arr[largest])
    largest = l;

  if (r < n && arr[r] > arr[largest])
    largest = r;

  if (largest != i) {
    int temp = arr[i];
    arr[i] = arr[largest];
    arr[largest] = temp;

    heapify(arr, n, largest);
  }
}

void heapSort(int arr[], int n) {
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);

  for (int i = n - 1; i > 0; i--) {
    int temp = arr[0];
    arr[0] = arr[i];
    arr[i] = temp;

    heapify(arr, i, 0);
  }
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;

    // sort left and right halves
    mergeSort(pData, l, m);
    mergeSort(pData, m + 1, r);

    // merge sorted halves
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    extraMemoryAllocated += n1 * sizeof(int) + n2 * sizeof(int);

    for (int i = 0; i < n1; i++)
      L[i] = pData[l + i];
    for (int j = 0; j < n2; j++)
      R[j] = pData[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
      if (L[i] <= R[j]) {
        pData[k] = L[i];
        i++;
      } else {
        pData[k] = R[j];
        j++;
      }
      k++;
    }

    while (i < n1) {
      pData[k] = L[i];
      i++;
      k++;
    }

    while (j < n2) {
      pData[k] = R[j];
      j++;
      k++;
    }

    free(L);
    free(R);
  }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData) {
  FILE *inFile = fopen(inputFileName, "r");
  int dataSz = 0;
  int i, n, *data;
  *ppData = NULL;

  if (inFile) {
    fscanf(inFile, "%d\n", &dataSz);
    *ppData = (int *)malloc(sizeof(int) * dataSz);
    // Implement parse data block
    if (*ppData == NULL) {
      printf("Cannot allocate memory\n");
      exit(-1);
    }
    for (i = 0; i < dataSz; ++i) {
      fscanf(inFile, "%d ", &n);
      data = *ppData + i;
      *data = n;
    }

    fclose(inFile);
  }

  return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz) {
  if (dataSz - 100 < 0) {
    for (int i = 0; i < dataSz; i++) {
      printf("%d ", pData[i]);
    }
    printf("\n");

  } else {
    int i, sz = dataSz - 100;
    printf("\tData:\n\t");
    for (i = 0; i < 100; ++i) {
      printf("%d ", pData[i]);
    }
    printf("\n\t");

    for (i = sz; i < dataSz; ++i) {
      printf("%d ", pData[i]);
    }
    printf("\n\n");
  }
}

int main(void) {
  clock_t start, end;
  int i;
  double cpu_time_used;
  char *fileNames[] = {"input1.txt", "input2.txt", "input3.txt", "input4.txt"};

  for (i = 0; i < 4; ++i) {
    int *pDataSrc, *pDataCopy;
    int dataSz = parseData(fileNames[i], &pDataSrc);

    if (dataSz <= 0)
      continue;

    pDataCopy = (int *)malloc(sizeof(int) * dataSz);

    printf("---------------------------\n");
    printf("Dataset Size : %d\n", dataSz);
    printf("---------------------------\n");

    printf("Heap Sort:\n");
    memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
    extraMemoryAllocated = 0;
    start = clock();
    heapSort(pDataCopy, dataSz);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
    printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
    printArray(pDataCopy, dataSz);

    printf("Merge Sort:\n");
    memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
    extraMemoryAllocated = 0;
    start = clock();
    mergeSort(pDataCopy, 0, dataSz - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
    printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
    printArray(pDataCopy, dataSz);

    free(pDataCopy);
    free(pDataSrc);
  }
}
