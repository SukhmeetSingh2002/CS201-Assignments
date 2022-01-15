#include <stdio.h>
#include <stdlib.h>

// color,distance, parent and time arrays
int *color;
int *parent;
int *discoverTime;
int *finishTime;

int time;

#define backEdge 10
#define forwardEdge 20
#define TreeEdge 30
#define CrossEdge 40
#define white 0
#define gray 1
#define black 2

struct adjacencyList
{
    int Edge;
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

void depthFirstSearch_Visit(int u)
{
    time++;
    discoverTime[u] = time;
    color[u] = gray;
    adjacencyList *v = (adjacencyList *)malloc(sizeof(adjacencyList));
    v = adjLists[u];
    while (v != NULL)
    {
        if (color[v->key] == gray)
            v->Edge = backEdge;
        if (color[v->key] == black)
        {
            if (discoverTime[u] < discoverTime[v->key])
                v->Edge = forwardEdge;
            else
                v->Edge = CrossEdge;
        }
        if (color[v->key] == white)
        {
            v->Edge = TreeEdge;
            parent[v->key] = u;
            depthFirstSearch_Visit(v->key);
        }
        v = v->next;
    }
    color[u] = black;
    time++;
    finishTime[u] = time;
}

void depthFirstSearch(int size)
{
    for (int i = 0; i < size; i++)
    {
        color[i] = white;
        parent[i] = -1;
    }
    time = 0;
    for (int i = 0; i < size; i++)
    {
        if (color[i] == white)
            depthFirstSearch_Visit(i);
    }
}

int main()
{
    // variables
    int numberOfVertices, leftVertex = 0, rightVertex = 0;
    char typeOfGraph, leftBracket, rightBracket, comma;

    // input no. of vertices
    printf("Enter the number of vertices: ");
    numberOfVertices = handleInputInt();

    // allocating memory
    adjLists = (adjacencyList **)malloc(sizeof(adjacencyList *) * numberOfVertices);
    color = (int *)malloc(sizeof(int) * numberOfVertices);
    parent = (int *)malloc(sizeof(int) * numberOfVertices);
    discoverTime = (int *)malloc(sizeof(int) * numberOfVertices);
    finishTime = (int *)malloc(sizeof(int) * numberOfVertices);

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

        leftBracket = handleInputChar();
        scanf("%d", &leftVertex);
        comma = handleInputChar();
        scanf("%d", &rightVertex);
        rightBracket = handleInputChar();

        // taking input
        while (leftVertex != -1 && rightVertex != -1)
        {
            inputGraph(numberOfVertices, leftVertex, rightVertex);

            leftBracket = handleInputChar();
            if (leftBracket == 'Q' || leftBracket == 'q')
                break;
            scanf("%d", &leftVertex);
            comma = handleInputChar();
            scanf("%d", &rightVertex);
            rightBracket = handleInputChar();
            if (leftVertex == -1 && rightVertex == -1)
                break;
        }
    }
    else if (typeOfGraph == 'U')
    {
        printf("Enters edges one by one of your Undirected graph. Once done, press ‘Q’: \n");

        leftBracket = handleInputChar();
        scanf("%d", &leftVertex);
        comma = handleInputChar();
        scanf("%d", &rightVertex);
        rightBracket = handleInputChar();

        // taking input
        while (leftVertex != -1 && rightVertex != -1)
        {
            inputGraph(numberOfVertices, leftVertex, rightVertex);
            inputGraph(numberOfVertices, rightVertex, leftVertex);

            leftBracket = handleInputChar();
            if (leftBracket == 'Q' || leftBracket == 'q')
                break;
            scanf("%d", &leftVertex);
            comma = handleInputChar();
            scanf("%d", &rightVertex);
            rightBracket = handleInputChar();
            if (leftVertex == -1 && rightVertex == -1)
                break;
        }
    }

    else
    {
        printf("Invalid input\n");
        return 0;
    }

    // printing list
    if (typeOfGraph == 'U')
        printf("Your undirected graph is as follows: \n");
    else
        printf("Your directed graph is as follows: \n");
    outputList(numberOfVertices);

    // performing bfs
    printf("The program runs the DFS algorithm on the graph entered.\n");
    depthFirstSearch(numberOfVertices);

    // printing time
    if (typeOfGraph == 'D')
        printf("The discovery time and the finishing time for the vertices of the directed graph are as follows: \n");
    else
        printf("The discovery time and the finishing time for the vertices of the undirected graph are as follows: \n");
    for (int i = 0; i < numberOfVertices; i++)
        printf("Vertex %d: discovery time %d, finishing time %d\n", i, discoverTime[i], finishTime[i]);

    // printing classification of edges
    printf("The classification of edges are as follows: \n");
    for (int i = 0; i < numberOfVertices; i++)
    {
        adjacencyList *v = (adjacencyList *)malloc(sizeof(adjacencyList));
        v = adjLists[i];
        while (v != NULL)
        {
            if (v->Edge == TreeEdge)
                printf("Edge (%d, %d): Tree\n", i, v->key);
            if (v->Edge == forwardEdge && typeOfGraph == 'D')
                printf("Edge (%d, %d): forward\n", i, v->key);
            if (v->Edge == CrossEdge && typeOfGraph == 'D')
                printf("Edge (%d, %d): Cross\n", i, v->key);
            if (v->Edge == backEdge && (typeOfGraph == 'D'))
                printf("Edge (%d, %d): Back\n", i, v->key);
            if (v->Edge == forwardEdge && typeOfGraph == 'U')
                printf("Edge (%d, %d): back\n", v->key, i);

            v = v->next;
        }
    }

    return 0;
}