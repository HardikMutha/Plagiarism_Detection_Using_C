#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 32
typedef struct heap
{
	int n;
	int arr[MAX];
} heap;


void init_heap(heap *h)
{
	h->n = 0;
	return;
}

# define MIN(a,b) ((a) < (b) ? a : b)
int min_array(int arr[], int a, int b, int c)
{
	int x = MIN(arr[a],arr[b]);
	int y = MIN(x,arr[c]);
	
	if(y == arr[a])
		return a;
	if(y == arr[b])
		return b;
	if(y == arr[c])
		return c;
	return -1;	
	
}

int heap_empty(heap h)
{
	return h.n == 0;
}

int heap_full(heap h)
{
	return h.n == MAX;
}	

void swap(int *arr, int a, int b)
{
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
	return;
}

void heap_insert(heap *h, int data)
{
	int child, parent;
	h->arr[h->n] = data;

	child = h->n;
	parent = (child - 1) / 2;
	
	// loop to bubble it up to proper position
	while(child > 0)
	{
		if(h->arr[child] < h->arr[parent])
		{
			swap(h->arr, child, parent);
			child = parent;
			parent = (parent - 1) / 2;
		}
		else
			break;
	}
	(h->n)++;
	return;
}

void heap_print(heap *h)
{
	for (int i = 0; i < h->n; i++)
	{
		printf("%d, ", h->arr[i]);
	}
	printf("\n");
	return;
}

void min_heapify(heap *h)
{
        int parent = 0;
        int c1 = parent * 2 + 1;
        int c2 = parent * 2 + 2;

        while(c1 < h->n)
        {
                int smallest = min_array(h->arr, c1, c2, parent);
                if(smallest == parent)
                        break;
                swap(h->arr, parent, smallest);
                parent = smallest;
                c1 = parent * 2 + 1;
                c2 = parent * 2 + 2;
        }
        return;
}

int heap_remove(heap *h)
{
	int x = h->arr[0];
	h->arr[0] =h->arr[h->n - 1];
	(h->n)--;

	int parent = 0;
	int lchild = parent * 2 + 1, rchild = parent * 2 + 2;
	while(lchild <  h->n)
	{
		
		int smallest = min_array(h->arr, lchild, rchild, parent);
		//int smallest = 1;
		if(smallest == parent)
			break;
		swap(h->arr, parent, smallest);
		parent = smallest;
		lchild = parent * 2 + 1;
		rchild = parent * 2 + 2;
		
	}
	return x;
}

void heap_sort(heap *h)
{
	int n = h->n;
	// assume h->arr is already a heap
	while((h->n) >= 1)
	{
		swap(h->arr, 0, h->n);
		(h->n)--;
		min_heapify(h);
	}
	h->n = n;
	return;
}

int main()
{
	int x;
	heap h;
	init_heap(&h);

	while(scanf("%d", &x) != -1)
	{
		heap_insert(&h, x);
	}
	heap_print(&h);	
	//while(!heap_empty(h))
	//{
	//	printf("%d\n ", heap_remove(&h));
	//}
	//printf("\n");
	heap_sort(&h);
	printf("Sorted: \n");
	heap_print(&h);
}
