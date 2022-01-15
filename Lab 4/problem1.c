#include <stdio.h>
#include <stdlib.h>

int heapSize=0;//size of the heap

int left(int *a,int i)
{
    return ((2*(++i))-1);    
}
int right(int *a,int i)
{
    return (((2*(++i))+1)-1);
}
int parent(int *a,int i)
{
    return (((++i)/2)-1);
}


void maxHeapyfy(int *a,int i)
{
    int leftChild=left(a,i),rightChild=right(a,i),temp=0,largest=i;
    if(leftChild<heapSize && a[i]<a[leftChild])//left child is greater
    {
        largest=leftChild;
    }
    if(rightChild<heapSize && a[largest]<a[rightChild])//right child is greater
    {
        largest=rightChild;
    }
    if(largest!=i)
    {
        temp=a[i];
        a[i]=a[largest];
        a[largest]=temp;
        maxHeapyfy(a,largest);
    }
}

void builMaxHeap(int *a)
{
    for (int i = heapSize/2; i >= 0; i--)
    {
        maxHeapyfy(a,i);
    }
    
}

int extractMax(int *a)
{
    int maxElt;
    if(heapSize<0)
    {
        printf("Underflow\n");
    }
    else
    {
        maxElt=a[0];
        a[0]=a[heapSize-1];
        heapSize--;
        maxHeapyfy(a,0);
    }
    return maxElt;
}

int main()
{
    int n,k,maxK;
    printf("Enter number of elements and k\n");
    scanf("%d",&n);
    scanf("%d",&k);

    heapSize=n;//set heap size = n 

    // allocating memory
    int *a=(int *)(malloc(n*sizeof(int)));

    // input elements
    printf("Enter %d elements \n",n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&a[i]);
    }

    // build max heap from the array
    builMaxHeap(a);
    
    // kth largest element
    for (int i = 0; i < k; i++)
    {
        maxK=extractMax(a);
    }
    
    // printing kth largest
    printf("The %dth largest element = %d\n",k,maxK);

    // freeing memory
    free(a);
    return 0;
}