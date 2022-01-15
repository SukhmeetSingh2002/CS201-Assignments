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


void minHeapyfy(int *a,int i)
{
    int leftChild=left(a,i),rightChild=right(a,i),temp=0,smallest=i;
    if(leftChild<heapSize && a[i]>a[leftChild])//left child is smaller
    {
        smallest=leftChild;
    }
    if(rightChild<heapSize && a[smallest]>a[rightChild])//right child is smaller
    {
        smallest=rightChild;
    }
    if(smallest!=i)
    {
        temp=a[i];
        a[i]=a[smallest];
        a[smallest]=temp;
        minHeapyfy(a,smallest);
    }
}

void builMinHeap(int *a)
{
    for (int i = heapSize; i >= 0; i--)
    {
        minHeapyfy(a,i);
    }
    
}


int main()
{
    int n,k,maxK;
    printf("Enter number of elements and k\n");
    scanf("%d",&n);
    scanf("%d",&k);

    heapSize=k;//set heap size = k

    // allocating memory to input elts and set S 
    int *a=(int *)(malloc(n*sizeof(int)));
    int *s=(int *)(malloc(k*sizeof(int)));

    // input elements
    printf("Enter %d elements \n",n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&a[i]);
    }

    // putting k elements in set s
    for (int i = 0; i < k; i++)
    {
        s[i]=a[i];
    }
    // build min heap of set S
    builMinHeap(s);
    
    for (int i = k; i < n; i++)
    {
        if(a[i]>s[0]) // if new elt is greater than min
        {
            s[0]=a[i];
            minHeapyfy(s,0);
        }
    }
    
    
    // printing kth largest
    printf("The %dth largest element = %d\n",k,s[0]);

    // freeing memory
    free(a);
    free(s);
    return 0;
}