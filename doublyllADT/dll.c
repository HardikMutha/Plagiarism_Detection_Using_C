#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"

/* typedef struct dllnode { */
/*     char *str; */
/*     struct dllnode *left; */
/*     struct dllnode *right; */
/* } dllnode; */

/* typedef struct dll { */
/*     dllnode *front; */
/*     dllnode *rear; */
/*     int len; */
/* } dll; */

void init_dll(dll *l) {
    l->front = NULL;
    l->rear = NULL;
    l->len = 0;
    return;
}

void append_dll(dll *l, char *input) {
    dllnode *temp = (dllnode *)malloc(sizeof(dllnode));
    temp->str = (char *)malloc(sizeof(char) * strlen(input) + 1);
    strcpy(temp->str, input);
    temp->left = NULL;
    temp->right = NULL;
    if(l->front == NULL) {
        l->front = temp;
        l->rear = temp;
        l->len++;    
    }
    l->rear->right = temp;
    temp->left = l->rear;
    l->rear = temp;
    l->len++;
    return;
}

void traverse_dll(dll l) {
    dllnode *temp = l.front;
    while(temp != NULL) {
        printf("%s\n", temp->str);
        temp = temp->right;
    }
    return;
}
