#include <stdio.h>
#include <stdlib.h>

#define white 0
#define gray 1
#define black 2

// color,distance and parent arrays
int *color;
int *distance;
int *parent;

// Queue implementation starts
int *queue;
int front=0;
int back=0;

void enqueue(int data)
{
    queue[front++]=data;
}

int isEmpty()
{
    if (front==back)
        return 0;
    return 1;
}
int dequeue()
{
    int x;
    if (front==0)
        return -1;
    else
    {
        x=queue[back];
        back++;
    }
    return x;
}

// Queue implementation ends

struct adjacencyList
{
    int key;
    struct adjacencyList *next;
};

typedef struct adjacencyList adjacencyList;

adjacencyList **adjLists;

void inputGraph(int size, int leftVertex, int rightVertex)
{
    adjacencyList *temp = (adjacencyList *)malloc(sizeof(adjacencyList));

    temp->key = rightVertex;
    temp->next = NULL;
    temp->next = adjLists[leftVertex];
    adjLists[leftVertex] = temp;
}

void outputList(int size)
{
    for (int i = 0; i < size; i++)
    {
        if (adjLists[i] == NULL)
        {
            printf("Vertex %d: NULL\n", i);
        }
        else
        {
            printf("Vertex %d: ", i);
            adjacencyList *temp2 = adjLists[i];
            while (temp2 != NULL)
            {
                printf("-> %d", temp2->key);
                temp2 = temp2->next;
            }
            printf("\n");
        }
    }
}

// handles \n
int handleInputInt()
{
    int x;
    scanf("%d", &x);
    return x;
}

// handles \n
char handleInputChar()
{
    char x;
    scanf("%c", &x);
    if (x == '\n')
    {
        scanf("%c", &x);
    }
    return x;
}

void BreadthFirstSearch(int source, int size)
{
    for (int i = 0; i < size; i++)
    {
        color[i] = 0;
        distance[i] = 0x7ffffffe; // infinity
        parent[i] = -1;
    }
    color[source] = gray;
    distance[source] = 0;
    parent[source] = -1;


    queue = (int *)malloc(sizeof(int)*size);
    enqueue(source);
    while (isEmpty())
    {
        int u = dequeue();
        adjacencyList *v = (adjacencyList *)malloc(sizeof(adjacencyList));
        v = adjLists[u];
        while (v != NULL)
        {
            if (color[v->key] == white)
            {
                color[v->key] = gray;
                distance[v->key] = distance[u] + 1;
                parent[v->key] = u;
                enqueue(v->key);
            }

            v = v->next;
        }
        color[u] = black;
    }
}

int main()
{
    // variables
    int numberOfVertices, leftVertex = 0, rightVertex = 0;
    char typeOfGraph,leftBracket,rightBracket,comma;

    // input no. of vertices
    printf("Enter the number of vertices: ");
    numberOfVertices = handleInputInt();

    // allocating memory
    adjLists = (adjacencyList **)malloc(sizeof(adjacencyList *) * numberOfVertices);
    color = (int *)malloc(sizeof(int) * numberOfVertices);
    distance = (int *)malloc(sizeof(int) * numberOfVertices);
    parent = (int *)malloc(sizeof(int) * numberOfVertices);

    //  initalize
    for (int i = 0; i < numberOfVertices; i++)
    {
        adjLists[i] = NULL;
    }

    // directed or undir.
    printf("Enter D for directed or U for undirected graphs: ");
    typeOfGraph = handleInputChar();

    // taking input for edges
    if (typeOfGraph == 'D')
    {
        printf("Enters edges one by one of your Directed graph. Once done, press ‘Q’: \n");

        leftBracket=handleInputChar();
        scanf("%d",&leftVertex);
        comma=handleInputChar();
        scanf("%d",&rightVertex);
        rightBracket=handleInputChar();

        // taking input
        while (leftVertex != -1 && rightVertex != -1)
        {
            inputGraph(numberOfVertices, leftVertex, rightVertex);

            leftBracket=handleInputChar();
            if (leftBracket=='Q' || leftBracket=='q')
                break;
            scanf("%d",&leftVertex);
            comma=handleInputChar();
            scanf("%d",&rightVertex);
            rightBracket=handleInputChar();
            if (leftVertex == -1 && rightVertex == -1)
                break;
        }
    }
    else if (typeOfGraph == 'U')
    {
        printf("Enters edges one by one of your Undirected graph. Once done, press ‘Q’: \n");

        leftBracket=handleInputChar();
        scanf("%d",&leftVertex);
        comma=handleInputChar();
        scanf("%d",&rightVertex);
        rightBracket=handleInputChar();

        // taking input
        while (leftVertex != -1 && rightVertex != -1)
        {
            inputGraph(numberOfVertices, leftVertex, rightVertex);
            inputGraph(numberOfVertices, rightVertex, leftVertex);

            leftBracket=handleInputChar();
            if (leftBracket=='Q' || leftBracket=='q')
                break;
            scanf("%d",&leftVertex);
            comma=handleInputChar();
            scanf("%d",&rightVertex);
            rightBracket=handleInputChar();
            if (leftVertex == -1 && rightVertex == -1)
                break;
        }
    }

    else
        printf("Invalid input\n");

    // printing list
    printf("Your undirected graph is as follows: \n");
    outputList(numberOfVertices);

    // performing bfs
    printf("Enter a source vertex s from where you wants to run the BFS algorithm on the graph you entered for problem 1a: ");
    int s;
    s = handleInputInt();
    BreadthFirstSearch(s,numberOfVertices);

    printf("BFS computed the following distances: \n");
    for (int i = 0; i < numberOfVertices; i++)
    {
        if(distance[i]!=0x7ffffffe)
            printf("The distance of the vertex %d from source vertex %d is: %d\n",i,s,distance[i]);
        else 
            printf("Not reachable\n");
    }
    

    return 0;
}