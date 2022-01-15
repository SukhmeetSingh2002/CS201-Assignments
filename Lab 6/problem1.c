#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    struct node* left;
    struct node* right;
};

typedef struct node node;

node* root; // pointer to root node

node* createNode()
{
    node* temp=(node* )malloc(sizeof(node));
    temp->left=NULL;
    temp->right=NULL;

    return temp;
}

int maxx(int a, int b)
{
    return (a > b ) ? a : b;
}

int height(node* temp)
{
    if(temp==NULL)
        return -1;
    return maxx(height(temp->left)+1,height(temp->right)+1);
}

int balanceFactor(node* temp)
{
    return height(temp->left)-height(temp->right);
}

node* rotateLeft(node* temp)
{
    node* child=temp->left;
    temp->left=child->right;
    child->right=temp;

    return child;
}

node* rotateRight(node* temp)
{
    node* child=temp->right;
    temp->right=child->left;
    child->left=temp;

    return child;
}

node* insertNode(int value)
{
    node* newNode=createNode();
    newNode->key=value;
    return newNode;
}



node* checkBalance(int value,node* temp)
{
    int bal=balanceFactor(temp);
    if (bal > 1 && value < temp->left->key) //LL
        return rotateLeft(temp);
 
    else if (bal < -1 && value > temp->right->key) //RR
        return rotateRight(temp);
 
    else if (bal > 1 && value > temp->left->key) //LR
    {
        temp->left = rotateRight(temp->left);
        return rotateLeft(temp);
    }
 
    else if (bal < -1 && value < temp->right->key) //RL
    {
        temp->right = rotateLeft(temp->right);
        return rotateRight(temp);
    }
    return temp;
}

node* insert(int value,node* nodeInsert)
{
    if(root==NULL)
    {
        root=createNode();
        root->key=value;
        return root;
    }
    node* temp=root;
    if(nodeInsert==NULL)
    {
        nodeInsert=insertNode(value);
        return nodeInsert;
    }
    else if(value<nodeInsert->key)
        nodeInsert->left=insert(value,nodeInsert->left);
    else if(value>nodeInsert->key)
        nodeInsert->right=insert(value,nodeInsert->right);
    return checkBalance(value,nodeInsert);
}

void search(int value)
{
    node* temp=root;
    while (temp!=NULL && temp->key!=value)
    {
        if(value>temp->key) temp=temp->right;
        else temp=temp->left;
    }
    if(temp==NULL)
    {
        printf("Not found\n");
        return;
    }
    printf("Found %d\n",temp->key);
    printf("Balance factor of %d is %d\n",temp->key,balanceFactor(temp));
    printf("Height of %d in the AVL tree is %d\n",temp->key,height(temp));
}

void printPreOrder(node* temp)
{
    if(temp!=NULL)
    {
        printf("%d ",temp->key);
        printPreOrder(temp->left);
        printPreOrder(temp->right);
    }
}

void printInOrder(node* temp)
{
    if(temp!=NULL)
    {
        printInOrder(temp->left);
        printf("%d ",temp->key);
        printInOrder(temp->right);
    }
}

int main()
{
    root=NULL;
    // inserting 0,1,2...24
    for (int i = 0; i <= 24; i++)
    {
        root=insert(i,root);
    }
    

    int data; // element to be inserted

    char garbage;
    char options;

    
    int exit=0; // to exit 
    while(!exit)
    {
        // asking for options
        printf("\ni) Insert :\ns) search :\np) Print Preorder and Inorder in Separate lines:\nq) Quit:\n");
        scanf("%c",&options);
        scanf("%c",&garbage);//scans "\n"
        switch (options)
        {
        case 'i':
            printf("Enter data to insert\n");
            scanf("%d",&data);
            scanf("%c",&garbage);//scans "\n"
            insert(data,root);
            // checkBalance(data);
            // checkBalance(data);
            break;
        case 's':
            printf("Enter data you want to search:");
            scanf("%d",&data);
            scanf("%c",&garbage);//scans "\n"
            search(data);
            break;
        case 'p':
            // PreOrder traversal
            printf("Preorder sequence:\n");
            printPreOrder(root);
            printf("\n");
            // inorder traversal
            printf("Inorder sequence:\n");
            printInOrder(root);
            printf("\n");
            break;
        case 'q':
            exit=1;
            break;
        
        default:
            printf("\nYou entered : %c\n",options);
            printf("Please enter i,s,p,q only (case sensitive)\n");
            break;
        }
    }
    return 0;

}