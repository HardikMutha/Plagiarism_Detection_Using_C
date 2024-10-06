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



/*
 * Basic structure of reading the files and processing:
 *  - read_file function:
 *      -> arguments: fd(int), filename(char *), words(*char[]), max_words_size(int)
 *      -> return type: int(words size)
 *      -> file is opened, and will be closed at the end of the function
 *      -> internally calls the read_line function to read each line of the line rather than having to store the complete file
 *      -> each line is fed to preprocessor function called tokenize
 *      -> tokenize function returns a string containing all words in the line separated by a comma
 *      -> the comma separated words are stored in an array of strings
 * 
 * - read_line function:
 *      -> arguments: fd(int), line(char *), max_line_size(int)
 *      -> return type: int(line size)
 *      -> reading the line from provided file
 *       
 * - tokenize:
 *      -> arguments: line(char *), words(char *), max_words_size(int)
 *      -> return type: int(words size)
 *      -> leading and trailing white spaces are ignored
 *      -> all punctuation marks(',', ';', ':', '.', '-') and sigle spaces are converted to commas separating each word on the given line
 *
 *
 * let's get started now :)
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "../List_ADT/linkedlist.h"
#include "../BST_ADT/bst.h"

#define MAX_SIZE 1024

int read_file   (int fd, char *filename, list *l);
int read_line   (int fd, char *line, int max_line_size);
int tokenize    (char *line, list *l); 



// int main(int argc, char *argv[]) {
//     int fd = 0;
//     char *filename; // words[MAX_SIZE][MAX_SIZE];
//     filename = (char *)malloc(sizeof(char) * 32);
//     list l;
//     init_SLL(&l);
    
//     if(argc != 3) {
//         printf("files not provided\n");
//         return 0;
//     }
//     // tokenization of first file:
//     strcpy(filename, argv[1]);
//     int tokens1 = read_file(fd, filename, &l); 
    
//     printf("tokens 1: %d\n", tokens1);
//     traverse(l);
//     free(filename);
//     return 0;
// }


int read_file(int fd, char *filename, list *l) {
    int token_count = 0;
    fd = open(filename, O_RDONLY);
    if(fd == -1) {
        perror("open failed");
        return errno;
    }
    char *line = (char *)malloc(sizeof(char) * MAX_SIZE);
    
    while(read_line(fd, line, MAX_SIZE)) {
        // calling the tokenization function  
        // line is read into the line
        // line will be passed to the tokenize function
        token_count += tokenize(line, l);
        // we will get tokenized words string with comma separated words
    }

    return token_count; // i is the length of array of strings words
}


int read_line(int fd, char *line, int max_line_size) {
    int length = 0; 
    char ch;
    while(length < max_line_size && read(fd, &ch, 1)) {
        if(ch != '\n') {
            line[length++] = ch;
        } else {
            break;
        }
    }

    line[length] = '\0';
    return length;
}

int is_punctuation(char ch) {
    if(ch == ',' || ch == '.' || ch == ':' || ch == ';')
        return 1;
    return 0;
}

int is_space(char ch) {
    if(ch == ' ' || ch == '\t' || ch == '\v')
        return 1;
    return 0;
}

char toLower(char ch) {
    if(ch >= 'a' && ch <= 'z')
        return ch;
    if(ch >= 'A' && ch <= 'Z')
        ch += ('a' - 'A');
    return ch;
}


int tokenize(char *line, list *l) {
    int i = 0; // for line traversal
    int j = 0; // for word traversal
    int tokens = 0;
    
    char *word = (char *)malloc(sizeof(char) * 64); 
    while(line[i] != '\0') {
        if(is_space(line[i]) || is_punctuation(line[i])) {
            if(!is_space(line[i-1]) && !is_punctuation(line[i-1])) {
                word[j] = '\0';
                append(l, word);
                j = 0;
                tokens++;
            }
            i++;
            continue;
        }
        else {
            word[j++] = line[i++];
        }
    }
    if(j != 0) {
        word[j] = '\0';
        append(l, word);
        tokens++;
    }
    return tokens;
}




// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "../BST_ADT/bst.h"
// #include "../string_tokenization/file_preprocess.h"
// #include "../List_ADT/linkedlist.h"

// #define MAX_SIZE 512

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

