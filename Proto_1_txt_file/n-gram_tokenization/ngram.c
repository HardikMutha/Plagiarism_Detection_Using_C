#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../BST_ADT/bst.h"
#include "../string_tokenization/file_preprocess.h"

#define MAX_SIZE 512

int main(int argc, char *argv){
    tree bigramToks;
    tree trigramToks;

    initBST(&bigramToks);
    initBST(&trigramToks);

    char *token;
    int i = 0, j = 0;
    char *words[64];
    char *csv_content = (char*)malloc(MAX_SIZE * sizeof(char));
    strcpy(csv_content, "apple,banana,grape,orange,mango");
    token = strtok(csv_content, ",");
    if(token){
        words[i] = token;
        i++;
    }
    while(token != NULL){
        token = strtok(NULL, ",");
        if(token){
            words[i] = token;
            i++;
        }
    }
    for(int j = 0; j < i; j++){
        printf("%s\n", words[j]);
    }

    // bigrams -
    char *bigrams;
    for(int j = 0; j < i - 1; j++){
        bigrams = (char*)malloc(strlen(words[j]) + strlen(words[j + 1]) + 1);
        strcpy(bigrams, words[j]);
        strcat(bigrams, words[j + 1]);
        insertValue(&bigramToks, bigrams);
        free(bigrams);
    }

    // trigrams -
    char *trigrams;
    for(int j = 0; j < i - 2; j++){
        trigrams = (char*)malloc(strlen(words[j]) + strlen(words[j + 1]) + strlen(words[j + 2]) + 1);
        strcpy(trigrams, words[j]);
        strcat(trigrams, words[j + 1]);
        strcat(trigrams, words[j + 2]);
        insertValue(&trigramToks, trigrams);
        free(trigrams);
    }

    inOrderTraversal(bigramToks);
    inOrderTraversal(trigramToks);

    free(csv_content);
    return 0;
}
// fgdn