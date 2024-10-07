/* getBigrams
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../BST_ADT/bst.h"
#include "../string_tokenization/file_preprocess.h"
// #include "../List_ADT/linkedlist.h"


void getBigrams(tree *t, list words){
    char *token;
    listnode *p = words.head;
    for(int j = 0; j < words.len - 1; j++){
        token = (char*)malloc(strlen(p->val) + strlen(p->next->val) + 1);
        strcpy(token, p->val);
        strcat(token, p->next->val);
        insertValue(t, token);
        free(token);
        p = p->next;
    }
    return;
}

void getTrigrams(tree *t, list words){
    char *token;
    listnode *p = words.head;
    for(int j = 0; j < words.len - 2; j++){
        token = (char*)malloc(strlen(p->val) + strlen(p->next->val) + strlen(p->next->next->val) + 1);
        strcpy(token, p->val);
        strcat(token, p->next->val);
        strcat(token, p->next->next->val);
        insertValue(t, token);
        free(token);
        p = p->next;
    }
    return;
}

int main(int argc, char *argv[]){

    list words_file1; // list to store words of file 1
    init_SLL(&words_file1);

    list words_file2; // list to store words of file 2
    init_SLL(&words_file2);


    // file reading -
    int fd = 0;
    char *filename; // words[MAX_SIZE][MAX_SIZE];
    filename = (char *)malloc(sizeof(char) * 32);

    if(argc != 3) {
        printf("files not provided\n");
        return 0;
    }

    strcpy(filename, argv[1]);
    int tokens1 = read_file(fd, filename, &words_file1);
    words_file1.len = tokens1;

    strcpy(filename, argv[2]);
    int tokens2 = read_file(fd, filename, &words_file2);
    words_file2.len = tokens2;

    free(filename);
    // End of file reading;


    // for file 1 - (initialization of BST for bigram, trigram token storage of file 1)
    tree bigramToks_file1;
    tree trigramToks_file1;
    initBST(&bigramToks_file1);
    initBST(&trigramToks_file1);

    // for file 2 - (initialization of BST for bigram, trigram token storage of file 2)
    tree bigramToks_file2;
    tree trigramToks_file2;
    initBST(&bigramToks_file2);
    initBST(&trigramToks_file2);


    // Bigram Tokenization for file1 and file2 -

    getBigrams(&bigramToks_file1, words_file1);
    getBigrams(&bigramToks_file2, words_file2);

    // calculate similarity check value for bigram tokenaization

    // free bst for bigram tokens (bigramToks_file1 and bigramToks_file2)


    // Trigram Tokenization for file1 and file2 -

    getTrigrams(&trigramToks_file1, words_file1);
    getTrigrams(&trigramToks_file2, words_file2);

    // calculate similarity check value for trigram tokenaization

    // free bst for trigram tokens (trigramToks_file1 and trigramToks_file2)


    // delete list of words -
    deleteList(&words_file1);
    deleteList(&words_file2);

    printf("file1-bigrams:\n");
    inOrderTraversal(bigramToks_file1);
    printf("\nfile2-bigrams:\n");
    inOrderTraversal(bigramToks_file2);

    printf("\nfile1-trigrams:\n");
    inOrderTraversal(trigramToks_file1);
    printf("\nfile2-trigrams:\n");
    inOrderTraversal(trigramToks_file2);

    destroyTree(&bigramToks_file1);
    destroyTree(&bigramToks_file2);

    destroyTree(&trigramToks_file1);
    destroyTree(&trigramToks_file2);

    // free(csv_content);
    return 0;
}

