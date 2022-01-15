#include <stdio.h>
#include <stdlib.h>

struct twoStacks
{
    int *stack;
    int top1;
    int top2;
};

typedef struct twoStacks twoStacks;
twoStacks *stacks ;

void display(int size)
{
    printf("Stack 1:\n");
    for (int i = (stacks->top1)-1; i >= 0; i--)
    {
        printf("%d\n",stacks->stack[i]);
    }
    
    printf("\nStack 2:\n");
    for (int i = (stacks->top2)+1; i < size; i++)
    {
        printf("%d\n",stacks->stack[i]);
    }
    printf("\n");
}

int isFull()
{
    return (stacks->top1) > stacks->top2;
}

int isNotEmpty(int whichStack,int size)
{
    if(whichStack==0)
        return (stacks->top1) > 0 ;
    else
        return (stacks->top2) < size-1;
}

void push(int i, int whichStack)
{
    if (!isFull())
    {
        if(whichStack==0)
            stacks->stack[(stacks->top1)++] = i;
        else
            stacks->stack[(stacks->top2)--] = i;
    }
    else
        printf("\n!!!!!!stack full!!!!!!\n\n");
}

void pop(int whichStack,int size)
{
    if (isNotEmpty(whichStack,size))
    {
        if(whichStack==0)
            ((stacks->top1)--);
        else
            ((stacks->top2)++);
    }
    else printf("\n!!!!Underflow!!!!!!!\n\n");
}

void inputStack(int n,int which)
{
    int x;
    while (n--)
    {
        printf("Enter element to push : ");
        scanf("%d", &x);
        push(x,which);
    }
}

int main()
{
    stacks=(twoStacks *)(malloc(sizeof(twoStacks)));
    int n,breakProg=1,checker=0,numbersPush,which=0;
    printf("Enter the size of array : ");
    scanf("%d",&n);
    stacks->stack=(int *)(malloc(n*(sizeof(int))));
    stacks->top1 = 0;  //pointing to 1st free space
    stacks->top2 = n-1; // same as above
    while (breakProg)
    {
        printf("Enter :\n1) 1 for push\n2) 2 for display \n3) 3 to pop \n4) 4 to exit the program\n");
        scanf("%d",&checker);
        switch (checker)
        {
        case 1:
            printf("How many numbers you want push? : ");
            scanf("%d", &numbersPush);
            printf("In which stack do you want push(1 or 2)? : ");
            scanf("%d", &which);
            inputStack(numbersPush,--which);
            break;
        case 2:
            display(n);
            break;
        case 3:
            printf("Enter which stack to pop(1 or 2)\n");
            scanf("%d", &which);
            pop(--which,n);
            break;
        case 4:
            printf("Thank you!!!\nNow exiting ...\n");
            free(stacks->stack);
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
Q-2(b)
We can implement two stacks as above i.e. one from starting and other from ending.
for the 3rd stack we can use the space inbetween them i.e. from top1 to top2 and copy the elements of 3rd stack when 
one of top1 or top2 changes, depending where is top3.
*/