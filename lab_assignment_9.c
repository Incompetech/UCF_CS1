#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// RecordType
struct RecordType {
  int id;
  char name;
  int order;
  struct RecordType *next; // create a next pointer (for linkedlist structure)
};

// Fill out this structure
struct HashType {
  struct RecordType *record; // create a pointer to a RecordType
};

// Compute the hash function
int hash(int x, int tableSize) {
  return x % tableSize; // hash function is x % tableSize
}

void insertRecord(struct HashType *hashTable, struct RecordType *record, int hashSz) {
  int index = hash(record->id, hashSz); 
  if (hashTable[index].record == NULL) {
    hashTable[index].record = record; 
                                      
  } else {
    struct RecordType *current = hashTable[index].record;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = record; 
  }
}
// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData, int *dataSz) {
  FILE *inFile = fopen(inputFileName, "r");
  int i, n;
  char c;
  struct RecordType *pRecord;
  *ppData = NULL;

  if (inFile) {
    fscanf(inFile, "%d\n", dataSz);
    *ppData =
        (struct RecordType *)malloc(sizeof(struct RecordType) * (*dataSz));
    if (*ppData == NULL) {
      printf("Cannot allocate memory\n");
      exit(-1);
    }
    for (i = 0; i < (*dataSz); ++i) {
      pRecord = *ppData + i;
      fscanf(inFile, "%d %c %d\n", &pRecord->id, &pRecord->name,
             &pRecord->order);
      pRecord->next = NULL;
    }
    fclose(inFile);
  }

  return *dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz) {
  int i;
  printf("\nRecords:\n");
  for (i = 0; i < dataSz; ++i) {
    printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
  }
  printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz) {
  int i;
  struct RecordType *currentRecord;

  for (i = 0; i < hashSz; ++i) {
    currentRecord = pHashArray[i].record;
    if (currentRecord != NULL) {
      printf("Index %d ->", i);
      while (currentRecord != NULL) {
        printf(" %d, %c, %d ->", currentRecord->id, currentRecord->name,
               currentRecord->order);
        currentRecord = currentRecord->next;
      }
      printf(" NULL\n");
    }
  }
}

int main(void) {
  struct RecordType *pRecords;
  struct HashType *pHashTable;
  int recordSz = 0;
  int hashSz = 8; // Size of the hash table
  int i, index;

  recordSz = parseData("input.txt", &pRecords, &recordSz);
  printRecords(pRecords, recordSz);

  // Allocate memory for the hash table
  pHashTable = (struct HashType *)malloc(sizeof(struct HashType) * hashSz);
  // Initialize the hash table
  for (i = 0; i < hashSz; ++i) {
    pHashTable[i].record = NULL;
  }

  // Insert the records into the hash table
  for (i = 0; i < recordSz; ++i) {
    insertRecord(pHashTable, &pRecords[i], hashSz);
  }
  displayRecordsInHash(pHashTable, hashSz);
  free(pHashTable);
  free(pRecords);
  return 0;
}
