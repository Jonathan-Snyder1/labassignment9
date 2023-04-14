#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order;
	struct RecordType *next;
};

// Fill out this structure
struct HashType
{
    struct RecordType *data;
    struct HashType *next;
};

// Compute the hash function
int hash(int x, int tableSize)
{
    return x % tableSize;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
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
    int index = hash(record->id, tableSize);

    if (hashTable[index].data == NULL)
    {
        hashTable[index].data = record;
    }
    else
    {
        struct RecordType *p = hashTable[index].data;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = record;
    }
}

// display records in the hash structure
void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
	int i;
    printf("\nHash Table:\n");
    for (i = 0; i < tableSize; ++i)
    {
        if (hashTable[i].data == NULL)
        {
            printf("Index %d -> NULL\n", i);
        }
        else
        {
            printf("Index %d -> ", i);
            struct RecordType *p = hashTable[i].data;
            while (p != NULL)
            {
                printf("%d, %c, %d", p->id, p->name, p->order);
                if (p->next != NULL)
                {
                    printf(" -> ");
                }
                p = p->next;
            }
            printf("\n");
        }
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize the hash table
    int hashTableSize = 10; // set the size of the hash table
    struct HashType *hashTable = (struct HashType *)calloc(hashTableSize, sizeof(struct HashType));
    if (hashTable == NULL)
    {
        printf("Cannot allocate memory\n");
        exit(-1);
    }

    // Insert records into hash table
    int i;
    for (i = 0; i < recordSz; i++)
    {
        insertRecord(hashTable, &pRecords[i], hashTableSize);
    }

    // Display
    displayRecordsInHash(hashTable, hashTableSize);

    // Free memory
    free(pRecords);
    free(hashTable);

    return 0;
}
