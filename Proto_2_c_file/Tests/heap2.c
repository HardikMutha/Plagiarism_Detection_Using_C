#include <stdio.h>
#include <stdlib.h>

typedef struct heap
{
    int *arr;
    int size;
    int rear;
} heap;

void init_heap(heap *h, int size)
{
    h->arr = (int *)malloc(sizeof(int) * size);
    h->size = size;
    h->rear = -1;
    return;
}

int isEmpty(heap h)
{
    if (h.rear == -1)
        return 1;
    return 0;
}

int parent(int index)
{
    return ((index - 1) / 2);
}

void swap(heap *h, int a, int b)
{
    if (a >= h->size || b >= h->size || a < 0 || b < 0)
        return;

    int temp = h->arr[a];
    h->arr[a] = h->arr[b];
    h->arr[b] = temp;

    return;
}

void insert_heap(heap *h, int k)
{

    h->rear++;
    h->arr[h->rear] = k;
    int i = h->rear;

    while (i > 0 && h->arr[i] > h->arr[parent(i)])
    {
        swap(h, i, parent(i));
        i = parent(i);
    }
    return;
}

void heapify(heap *h)
{
    int j = 0;
    while (j <= h->rear)
    {
        int lchild = 2 * j + 1;
        int rchild = 2 * j + 2;
        int largest = j;

        if (lchild <= h->rear && h->arr[lchild] > h->arr[largest])
            largest = lchild;

        if (rchild <= h->rear && h->arr[rchild] > h->arr[largest])
            largest = rchild;

        if (largest != j)
        {
            swap(h, j, largest);
            j = largest;
        }
        else
            break; // break if  current node is in correct position
    }
    return;
}

void print_heap(heap h)
{ // Displays heap elements.
    for (int i = 0; i <= h.rear; i++)
    {
        printf("%d,", h.arr[i]);
    }
    printf("\n");
    return;
}

void heap_sort(heap *h)
{
    int rear = h->rear;
    if (isEmpty(*h))
        return;

    for (int i = h->rear; i >= 0; i--)
    {
        swap(h, i, 0);
        h->rear--;
        h->size--;
        heapify(h);
    }

    h->rear = rear;
    return;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        perror("Invalid Usage!\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        perror("Error Opening File\n");
        return 1;
    }

    heap h;
    init_heap(&h, 100);

    int d;
    while (fscanf(file, "%d", &d) != EOF)
        insert_heap(&h, d);

    printf("\nFormed heap : ");
    print_heap(h);

    printf("Sorted Heap :");
    heap_sort(&h);
    print_heap(h);
    printf("\n");
    fclose(file);
    return 0;
}