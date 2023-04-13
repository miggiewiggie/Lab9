#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType* next;
    // create a next pointer (for linkedlist structure)
};

// Fill out this structure
struct HashType
{
    struct RecordType* record;
    // create a pointer to a RecordType
};

// Compute the hash function
int hash(int x, int tableSize)
{
    int hashFunc = x % tableSize;
    
    return hashFunc;
    // hash function is x % tableSize
}

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    
    // call the hash function to get the index
    // if the RecordType at that index is NULL
    int recordsize = parseData("input.txt", &record);

    for(int i = 0; i < recordsize; i++){
        
        int index = hash(record[i].id, tableSize);
       
        
        

        if(hashTable[index].record == NULL)
        {
            struct RecordType* pRecordIndex = &(record[index]);
            hashTable[index].record = (struct RecordType*)malloc(sizeof(struct RecordType));
            hashTable[index].record = pRecordIndex;
            hashTable[index].record->next = NULL;
            // set 'record' equal to the HashType pointer in the table at index
        }
        else
        {
            struct RecordType* newNode = (struct RecordType*)malloc(sizeof(struct RecordType)); //Creates node for record
            struct RecordType* tempPointer;
            newNode->next = NULL;
            newNode->id = record[i].id;
            newNode->name = record[i].name;
            newNode->order = record[i].order;
            tempPointer = hashTable[index].record; //Node points to the index in the hash table where the chain should be
            //The head
            while(tempPointer != NULL && tempPointer->next != NULL)
            {
                tempPointer = tempPointer ->next;
            }

            if(tempPointer != NULL)
                tempPointer->next = newNode;
            else
                hashTable[index].record = newNode;
        }
        // else
            // traverse to the end of the linkedlist and add 'record' to the end of it
     }
    
    }

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
    // for each entry in the table
    printf("Hash Table Records\n");
    printf("==================\n");
    for(int i = 0; i < tableSize; i++)
    {
        if(hashTable[i].record->next == NULL)
            printf("\t Index %d -> [%d, %c, %d]  -> NULL", i, hashTable[i].record->id, hashTable[i].record->name, hashTable[i].record->order);

        else
        {
            printf("\t Index %d -> [%d, %c, %d]", i, hashTable[i].record->id, hashTable[i].record->name, hashTable[i].record->order);
            while(hashTable[i].record->next != NULL)
            {
                hashTable[i].record = hashTable[i].record->next;
                
                printf(" -> [%d, %c, %d]", hashTable[i].record->id, hashTable[i].record->name, hashTable[i].record->order);
            }
            printf(" -> NULL");
        }
        printf("\n\n");
    }
        // print the contents in that index
        // The output should look like this (for example): "Index 1 -> 21715, Q, 16 -> 28876, a, 26 -> NULL"
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize the hash table
    struct HashType* pHashRecords;

    // create a variable hashTableSize and assign it a value
    int hashTableSize = 11;

    // initialize a hashTable, use calloc (so everything is assigned to NULL)
    pHashRecords = (struct HashType*)calloc(hashTableSize, sizeof(struct HashType));

    // for each record in pRecords, insert it into the hash table using the insertRecord function
    insertRecord(pHashRecords, pRecords, hashTableSize);

    // call the display records function

    displayRecordsInHash(pHashRecords, hashTableSize);

    // free all the allocated memory
    free(pRecords);
    free(pHashRecords);

    return 0;
}
