#include <stdio.h>
#include <stdlib.h>

struct unregularLinkList
{
    int item;
    struct unregularLinkList *next;
};

typedef struct unregularLinkList unregularLinkList;

unregularLinkList *head = NULL;

void insert(int item)
{
    unregularLinkList *temp = (unregularLinkList *)malloc(sizeof(unregularLinkList));
    temp->item = item;
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
    }
    else
    {
        temp->next = head;
        head = temp;
    }
}

void display()
{
    unregularLinkList *temp;
    if (head == NULL)
        printf("Empty\n");
    else
    {
        temp = head;
        while (temp != NULL)
        {
            printf("%d ", temp->item);
            temp = temp->next;
        }
    }
    printf("\n");
}

void deleteList()
{
    unregularLinkList *temp = head;
    if (head == NULL)
    {
        printf("List empty");
    }
    else
    {
        while (head != NULL)
        {
            head = head->next;
            free(temp);
            temp = head;
        }
    }
}

void findItem(int item)
{
    unregularLinkList *temp = head;
    unregularLinkList *node;
    printf("\n");
    if (item == head->item)
        display();
    else
    {
        while ((temp->next)->item != item)
        {
            temp = temp->next;
            if (temp->next == NULL)
            {
                printf("Not found \"%d\" in linkList\n", item);
                return;
            }
        }
        node = temp->next;
        temp->next = node->next;
        node->next = head;
        head = node;
        display();
    }
}

void inputList(int n)
{
    int x;
    while (n--)
    {
        printf("Enter element to input : ");
        scanf("%d", &x);
        insert(x);
    }
}

int main()
{
    int checker = 0, numbers = 0, findNumber = 0;
    int breakProg = 1;
    while (breakProg)
    {
        printf("Enter :\n1) 1 for input\n2) 2 for display \n3) 3 for find number\n4) 4 to exit the program\n");
        scanf("%d",&checker);
        switch (checker)
        {
        case 1:
            printf("How many numbers u want to enter? : ");
            scanf("%d", &numbers);
            inputList(numbers);
            break;
        case 2:
            display();
            break;
        case 3:
            printf("Enter the number to find and bring to front\n");
            scanf("%d", &findNumber);
            findItem(findNumber);
            break;
        case 4:
            printf("Thank you!!!\nNow deleting the link list and exiting ...\n");
            deleteList();
            breakProg = 0;
            break;
        default:
            printf("Please enter a valid number\n");
            break;
        }
    }
    return 0;
}

/*
Q-1(a)
Inputing a single integer takes O(1) so inserting n,n-1,...1 will take O(n) time complexity

Q-1(b)
(2n+2c(m-1))=O(n+m)

Q-1(c)
T(i)=n*(k+n-1)
    =O(n(n+k))

*/