#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

node *getNode(int val)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}

void initGraph(graph *g, int vertices)
{
    g->numberVertices = vertices;
    g->lists = (node **)malloc(sizeof(node *) * vertices);
    for (int i = 0; i < vertices; i++)
    {
        g->lists[i] = NULL;
    }
    return;
}

void addEdge(graph *g, int src, int dest)
{
    // from src to dest
    node *newNode = getNode(dest);
    newNode->next = g->lists[src];
    g->lists[src] = newNode;
    // from dest to src Undirected only
    node *newNode2 = getNode(src);
    newNode2->next = g->lists[dest];
    g->lists[dest] = newNode2;
}

void printGraph(graph g)
{
    for (int i = 0; i < g.numberVertices; i++)
    {
        printf("%c -> ", (i + 'a'));
        node *temp = g.lists[i];
        while (temp)
        {
            printf("%c,", (temp->data + 'a'));
            temp = temp->next;
        }
        printf("\n");
    }
    return;
}

void free_graph(graph *g)
{
    for (int i = 0; i < g->numberVertices; i++)
    {
        node *temp = g->lists[i];
        while (temp)
        {
            node *curr = temp;
            temp = temp->next;
            free(curr);
        }
        g->lists[i] = NULL;
    }
    return;
}

void DepthFirstSearch(graph g)
{
    int *visited = (int *)calloc(g.numberVertices, sizeof(int));
    DFS(g, visited, 0);
    printf("\n");
    return;
}

void DFS(graph g, int *visited, int val)
{
    visited[val] = 1;
    printf("%c ", val + 'a');
    node *temp = g.lists[val];
    while (temp)
    {
        if (!visited[temp->data])
            DFS(g, visited, temp->data);
        temp = temp->next;
    }
    return;
}

void BFS(graph g)
{
    int *visited = (int *)calloc(g.numberVertices, sizeof(int));
    queue q;
    initqueue(&q, (g.numberVertices + 10));
    printf("%c ", 0 + 'a');
    visited[0] = 1;
    node *temp = g.lists[0];
    while (temp)
    {
        if (!visited[temp->data])
        {
            enqueue(&q, temp);
            visited[temp->data] = 1;
        }
        temp = temp->next;
    }
    while (!isEmpty(q))
    {
        node *temp = Front(q);
        dequeue(&q);
        printf("%c ", temp->data + 'a');
        visited[temp->data] = 1;
        node *temp2 = g.lists[temp->data];
        while (temp2)
        {
            if (!visited[temp2->data])
            {
                enqueue(&q, temp2);
                visited[temp2->data] = 1;
            }
            temp2 = temp2->next;
        }
    }
    printf("\n");
    return;
}