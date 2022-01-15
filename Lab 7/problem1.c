#include <stdio.h>
#include <stdlib.h>

struct linkList
{
    int key;
    struct linkList *prev;
    struct linkList *next;
};

typedef struct linkList linkList;

linkList **hashTable;

int hashFunction(int k, int m)
{
    return (k % m + m) % m;
}

void insert(int key, int sizeOfHash)
{
    int slotNumber = hashFunction(key, sizeOfHash);
    linkList *slot = hashTable[slotNumber];
    // printf("You got slot number %d\n", slotNumber);
    if (slot == NULL)
    {
        // printf("\n\nIt was null\n\n");
        hashTable[slotNumber] = (linkList *)(malloc(sizeof(linkList)));
        hashTable[slotNumber]->key = key;
        hashTable[slotNumber]->prev = NULL;
        hashTable[slotNumber]->next = NULL;
    }
    else
    {
        linkList *temp = (linkList *)(malloc(sizeof(linkList)));
        temp->key = key;
        temp->prev = NULL;
        temp->next = hashTable[slotNumber];
        hashTable[slotNumber]->prev = temp;
        hashTable[slotNumber] = temp;
    }
}
int search(int key, int sizeOfHash)
{
    int slot = hashFunction(key, sizeOfHash);
    if (hashTable[slot] == NULL)
        return -1;
    else
    {
        linkList *temp = (linkList *)(malloc(sizeof(linkList)));
        temp = hashTable[slot];
        while (temp != NULL)
        {
            if (temp->key != key)
                temp = temp->next;
            else if (temp->key == key)
                return slot;
        }
        if(temp==NULL)
            return -1;
    }
}
void delete (int key, int sizeOfHash)
{
    if (search(key, sizeOfHash) == -1)
        printf("Not present So can't delete\n");
    else
    {
        int slot = hashFunction(key, sizeOfHash);
        linkList *temp = (linkList *)(malloc(sizeof(linkList)));
        temp = hashTable[slot];
        while (temp != NULL)
        {
            if (temp->key != key)
                temp = temp->next;
            if (temp->key == key)
                break;
        }
        if (temp->next == NULL && temp->prev != NULL)
            temp->prev->next = NULL;
        else if (temp->next == NULL && temp->prev == NULL)
            hashTable[slot] = NULL;
        else if (temp->next != NULL && temp->prev == NULL)
        {
            hashTable[slot] = temp->next;
            temp->next->prev = NULL;
        }
        else
        {
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
        }
    }
}
void display(int sizeOfHash)
{
    printf("\n\n");
    linkList *slot;
    for (int i = 0; i < sizeOfHash; i++)
    {
        printf("Index %d : ", i);
        slot = hashTable[i];
        if (slot == NULL)
        {
            printf("NULL");
        }
        else
        {
            while (slot != NULL)
            {
                printf("%d ", slot->key);
                slot = slot->next;
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int data, options, sizeOfHash;

    printf("Enter hash table size m: ");
    scanf("%d", &sizeOfHash);

    hashTable = (linkList **)(malloc(sizeOfHash * sizeof(linkList *)));

    int exit = 0; // to exit
    while (!exit)
    {
        // asking for options
        printf(" \
        1. Insert\n \
        2. Delete\n \
        3. Search\n \
        4. Display\n \
        5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &options);
        switch (options)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &data);
            insert(data, sizeOfHash);
            break;
        case 2:
            printf("Enter the element to be deleted: ");
            scanf("%d", &data);
            delete (data, sizeOfHash);
            break;
        case 3:
            printf("Enter data you want to search:");
            scanf("%d", &data);
            int result = search(data, sizeOfHash);
            if (result == -1)
                printf("Not present\n");
            else
                printf("\n\n%d is present in slot number %d\n\n",data ,result);

            break;
        case 4:
            display(sizeOfHash);
            break;
        case 5:
            exit = 1;
            break;

        default:
            printf("\nYou entered : %d\n", options);
            printf("\n\nPlease enter 1,2,3,4,5 only \n\n");
            break;
        }
    }
    return 0;
}