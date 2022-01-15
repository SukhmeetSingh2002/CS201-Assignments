#include <stdio.h>
#include <stdlib.h>

struct node
{
    int n;
    int *key;
    int leaf;
    struct node **c;

};

typedef struct node node;

node* root;

node* createTree(int t){
    node* temp=(node*)malloc(sizeof(node));
    temp->leaf=1;
    temp->n=0;
    temp->key=(int*)malloc(((2*t)-1)*sizeof(int));
    temp->c=(node**)malloc(((2*t))*sizeof(node*));
    for (int i = 0; i <= 2*t; i++)
    {
        temp->c[i]=NULL;
    }
    
    return temp;
}


void splitChild(node* parent,int minDegree,int ii){

    node *child=parent->c[ii];//pointer to child

    node* temp=createTree(minDegree);// other partn of spilited node
    temp->n=minDegree-1;
    temp->leaf=child->leaf;


    int midOfChild=(minDegree-1);

    // update array of children of parent
      for(int i=parent->n;i>ii;i--){
        parent->key[i]=parent->key[i-1];
        parent->c[i+1]=parent->c[i];
    }

    parent->key[ii]=child->key[minDegree-1];
    parent->n=parent->n+1;
    // new node
    parent->c[ii+1]=temp;


    child->n=minDegree-1;
    // updating keys of temp
    for (int i = 0; i < temp->n; i++)
    {
        temp->key[i]=child->key[minDegree+i];
    }
    
    // updating child of temp if not a leaf
    if(!(child->leaf))
    {
        for (int i = 0; i <= temp->n; i++)
        {
            temp->c[i]=child->c[midOfChild+1+i];
            // child->c[i+minDegree]=NULL;
        }
    }

}

void insertNonFull(node* roott,int minDegree,int elt){
    if(roott->leaf)
    {
        int i=roott->n-1;
        while(roott->key[i]>elt && i>=0) 
        {
            roott->key[i+1]=roott->key[i];
            i--;
        }
        roott->key[i+1]=elt;
        roott->n=roott->n+1;
    }
    else
    {
        int i=0;    
        while(roott->key[i]<elt && i<roott->n) i++;
        if(roott->c[i]->n==2*minDegree-1)
        {
            splitChild(roott,minDegree,i);
            if(elt>roott->key[i])
                i++;
        }
        insertNonFull(roott->c[i],minDegree,elt);

    }
}
    
void insertTree(node* rootIn,int minDegree,int elt){
    if(root->n==2*minDegree-1)
    {
        node* temp=createTree(minDegree);
        temp->leaf=0;
        temp->c[0]=rootIn;
        root=temp;
        splitChild(root,minDegree,0);
        insertNonFull(root,minDegree,elt);
    }
    else insertNonFull(root,minDegree,elt);
}

void searchTree(node* roott,int elt){
    int i=0;
    if(roott->leaf)
    {
        while(roott->key[i]<elt && i<roott->n) i++;
        if(roott->key[i]==elt)
        {
            printf("Found %d\n",elt);
            return;
        }
        else printf("Not found\n");
    }
    else
    {
        while(roott->key[i]<elt && i<roott->n) i++;
        if(roott->key[i]==elt)
        {
            printf("Found %d\n",elt);
            return;
        }
        else searchTree(roott->c[i],elt);
    }
}
void treeMin(node* roott){
    if(roott->leaf)
        printf("%d\n",roott->key[0]);
    else treeMin(roott->c[0]);
}

void inOrderTraverseTree(node* roott){
    if(roott!=NULL)
    {
        for (int i = 0; i < roott->n+1; i++)
        {
            if(!roott->leaf)
            inOrderTraverseTree(roott->c[i]);
            if(i<roott->n)
                printf("%d ",roott->key[i]);
        }
    }
}

int main()
{
    int t, search, numOfElt,element;
    char garbage;
    char choice;

    
    // asking value of t
    printf("Enter the minimum degree of the B-tree t: ");
    scanf("%d",&t);
    scanf("%c",&garbage);//scan "\n"

    root=createTree(t); //root of the tree

    // asking A or B
    printf("Enter A or B: ");
    scanf("%c",&choice);

    // if input is A
    if(choice=='A')
    {
        // insert 100,99,...1
        for (int i = 100; i >0; i--)
        {
            insertTree(root,t,i);
        }
            
        // inorder
        scanf("%c",&garbage);
        inOrderTraverseTree(root);

        // asking elt to search
        printf("\nEnter an element to search:");
        scanf("%d",&search);
        searchTree(root,search);
    }

    else
    {   
        char options;
        int exit=0; // to exit 
        while(!exit)
        {
            // asking for options
            printf("You have the following options: I for insertion, S for search, M for finding minimum, T for traversing theB-tree, E for exit\n Enter your option : ");
            scanf("%c",&garbage);//scans "\n"
            scanf("%c",&options);

            switch (options)
            {
            case 'I':
                // code for number of elts to insert
                printf("Enter number of elements you wanted to enter: ");
                scanf("%d",&numOfElt);
                printf("Enter %d elements in new line\n ",numOfElt);
                for (int i = 0; i < numOfElt; i++)
                {
                    scanf("%d",&element);
                    insertTree(root,t,element);
                }
                
                break;
            case 'S':
                // asking elt to search
                printf("Enter an element to search:");
                scanf("%d",&search);
                searchTree(root,search);
                break;
            case 'M':
                // minimun element
                printf("Minimum element is: ");
                treeMin(root);
                break;
            case 'T':
                // inorder traversal
                inOrderTraverseTree(root);
                printf("\n");
                break;
            case 'E':
                // code to exit
                exit=1;
                break;
            
            default:
                printf("Please enter I,S,M,T,E only (case sensitive)\n");
                break;
            }
        }
    }
    return 0;
    
}