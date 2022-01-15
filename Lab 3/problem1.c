#include <stdio.h>
#include <stdlib.h>

struct linkList
{
    // int node;
    struct linkList* next;
};

typedef struct linkList linkList;

int ctr;

// Head o linklist
linkList* head=NULL;

// insert an item in linkList
linkList* insert(/* int item */)
{
    linkList *temp = (linkList *)malloc(sizeof(linkList));
    linkList *ptr=head;
    // temp->node = item;
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
    }
    else
    {
       while (ptr->next!=NULL)
       {
           ptr=ptr->next;
       }
       ptr->next=temp;
    }
    return temp;
}

// free all the pointers
void deleteList(int size)
{
    linkList *temp = head;
    if (head == NULL)
    {
        printf("List empty");
    }
    else
    {
        while (size--)
        {
            head = head->next;
            free(temp);
            temp = head;
        }
    }
}

// input linkList
void inputList(int sizeWithoutCycle, int lengthOfCycle)
{
    linkList* last,*temp;//These are only used for inserting in cycle and only head pointer is used in rest of the program
    while (sizeWithoutCycle--)
    {
        temp=insert();
    }
    if(lengthOfCycle-- >0)
    {
        last=insert();//start of cycle
        while (lengthOfCycle--)
        {
            temp=insert();
        }
        temp->next=last;
        
    }
}

// tells wheather there is a cycle or not
int detectCycle(int *isLoop,int ctr)
{
    linkList *prev = NULL,*curr=head,*next=head;
    while (curr!=NULL)
    {
        next=curr->next;
        curr->next=prev;//reversing the pointer
        prev=curr;
        curr=next;
        ctr++;
    }
    if (prev==head && head->next!=NULL)//there is a loop
    {
        *isLoop=ctr;
    }
    // recontsructing the linkList
    curr=prev;
    prev=NULL;
    while (curr!=NULL)
    {
        next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }
    return *isLoop;    
}

// calculating distance of cycle from start
int detectFindStart(int *size,int ctr)
{
    int isLoop=0;
    if(detectCycle(&isLoop,ctr))
    {
        int cycleLength=0;
        linkList *slow = head,*fast=head;
        while (fast!=NULL)
        {
            fast=fast->next->next;
            slow=slow->next;
            if(fast==slow)
                break;
        }
        do
        {
            slow=slow->next;
            cycleLength++;
        } while (fast!=slow);
        *size=cycleLength;
        return ((isLoop-1-cycleLength)/2);
    }
    else
    {
        printf("The linked list contains no cycle.\n");
        return -1;
    }
}

void swappp(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    // INPUT VARIABLES
    char cycle;
    int sizeWithoutCycle,lengthOfCycle=-1;
    // OUTPUT AND INTERNAL PROCESSING VARIABLES
    int lengthcycleINTERNAL/*Length of cycle*/,distaceFromStartINTERNAL/*Distace of cycle*/;
    ctr=0;
    // ctr = c +2m +1 (where c=lengthcycleINTERNAL and m=distaceFromStartINTERNAL)

    // taking input
    printf("Press Y for linked list with a cycle and N for without cycles: ");
    scanf("%c",&cycle);

    if (cycle=='Y')
    {
        // taking the input
        printf("Enter the length of cycle in the linked list: ");
        scanf("%d",&lengthOfCycle);
        printf("Enter the distance (number of edges) of the start node of the cycle from the head of the linked list: ");
        scanf("%d",&sizeWithoutCycle);

    }
    // if without cycle
    else if (cycle=='N')
    {
        // taking the input
        printf("Enter the size (number of edges) of linked list without cycle: ");
        scanf("%d",&sizeWithoutCycle);

    }
    else
    {
        printf("Please enter \"Y\" or \"N\" only.");
        return 0;
    }
    
    if(lengthOfCycle==1 && sizeWithoutCycle==0)
        swappp(&lengthOfCycle,&sizeWithoutCycle);
    // creating linkList
    inputList(sizeWithoutCycle,lengthOfCycle);
    distaceFromStartINTERNAL=detectFindStart(&lengthcycleINTERNAL,ctr);

    // output
    if(distaceFromStartINTERNAL!=-1)
    {
        printf("The linked list has a cycle of length %d and the distance of the start node of the cycle from the head of the linked list is %d.\n",lengthcycleINTERNAL,distaceFromStartINTERNAL);
        deleteList(lengthOfCycle+sizeWithoutCycle);
    }
    else
    {
        if(head!=NULL)
        {
            deleteList(ctr);
        }
        else
            printf("Empty \n");
    }

    
    return 0;
}






/*

LinkList is delibratelty kept empty (only next pointer is stored) as mentioned in question.
It can be done by just uncommeting corresponding line in struct. and insert function

Q-1(b)
It works by reversing the pointers.
This was taught in GE103 course.

In DetectCycle funct. a pointer traverses the linkList and reversers the pointer of the previous node. 
If there is a cycle then the pointer will finally reach at the head node and cycle will be detected. If no cycle is detected
then it will reach NULL pointer.

eg: suppose LinkList is 1->2->3->4->5->2
then it will become 1<-2<-3<-4 5->2: when ptr reaches 5
then it will become 1<-2<-3<-4<-5 2: when ptr reaches 2
then it will become 1->2<-3<-4<-5<-2: at end of traversal

Q-2(b)
It uses two pointers fast and slow and this was taught in GE103 course.

The fast pointer moves 2 nodes and slow moves one node at a time. Eventually they will meet at a point after
they enter the cycle. Because by the concept of relative velocity(using physics) they are approahing each 
other thus will eventually meet. 
Then we move one pointer one step forward till it meets the other. This way we get c=length of cycle.

detectCycle fucnt. traves the cycle elements one time and other two times and thus it returns k=c+2m+1

we get (k-c-1)/2=(c+2m+1-c-m)/2 = m
thus we get m = distance b/w cycle and head node.s

*/