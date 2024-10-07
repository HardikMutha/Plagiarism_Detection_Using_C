
#include "../mainheader.h"

void getBigrams(tree *t, list words, int *total_bigrams_file)
{
    char *token;
    listnode *p = words.head;
    for (int j = 0; j < words.len - 1; j++)
    {
        token = (char *)malloc(strlen(p->val) + strlen(p->next->val) + 1);
        strcpy(token, p->val);
        strcat(token, p->next->val);
        int x = insertValue(t, token);
        if (x == 1)
            (*total_bigrams_file)++;
        free(token);
        p = p->next;
    }
    return;
}

void getTrigrams(tree *t, list words, int *total_trigrams_file)
{
    char *token;
    listnode *p = words.head;
    for (int j = 0; j < words.len - 2; j++)
    {
        token = (char *)malloc(strlen(p->val) + strlen(p->next->val) + strlen(p->next->next->val) + 1);
        strcpy(token, p->val);
        strcat(token, p->next->val);
        strcat(token, p->next->next->val);
        int x = insertValue(t, token);
        if (x == 1)
            (*total_trigrams_file)++;
        free(token);
        p = p->next;
    }
    return;
}

int main(int argc, char *argv[])
{

    list words_file1; // list to store words of file 1
    init_SLL(&words_file1);

    list words_file2; // list to store words of file 2
    init_SLL(&words_file2);

    // file reading -
    int fd = 0;
    char *filename; // words[MAX_SIZE][MAX_SIZE];
    filename = (char *)malloc(sizeof(char) * 32);

    if (argc != 3)
    {
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
    int total_bigrams_file1 = 0;
    int total_bigrams_file2 = 0;
    getBigrams(&bigramToks_file1, words_file1, &total_bigrams_file1);
    getBigrams(&bigramToks_file2, words_file2, &total_bigrams_file2);

    // calculate similarity check value for bigram tokenaization

    get_intersection_of_tokens(bigramToks_file1, bigramToks_file2);
    double Jaccard_bigram_similarity_file1 = getJaccardSimScore(intersection_of_tokens, total_bigrams_file1);
    double Jaccard_bigram_similarity_file2 = getJaccardSimScore(intersection_of_tokens, total_bigrams_file2);

    // free bst for bigram tokens (bigramToks_file1 and bigramToks_file2)
    destroyTree(&bigramToks_file1);
    destroyTree(&bigramToks_file2);

    /*Code for Bigram End*/

    /*Code for Trigram starts*/

    // Trigram Tokenization for file1 and file2 -

    intersection_of_tokens = 0; // set the intersection_of_tokens(global variable) back to zero for trigram tokens

    int total_trigrams_file1 = 0;
    int total_trigrams_file2 = 0;

    getTrigrams(&trigramToks_file1, words_file1, &total_trigrams_file1);
    getTrigrams(&trigramToks_file2, words_file2, &total_trigrams_file2);

    // calculate similarity check value for trigram tokenaization

    get_intersection_of_tokens(trigramToks_file1, trigramToks_file2);
    double Jaccard_trigram_similarity_file1 = getJaccardSimScore(intersection_of_tokens, total_trigrams_file1);
    double Jaccard_trigram_similarity_file2 = getJaccardSimScore(intersection_of_tokens, total_trigrams_file2);

    // free bst for trigram tokens (trigramToks_file1 and trigramToks_file2)

    // delete list of words -
    deleteList(&words_file1);
    deleteList(&words_file2);

    destroyTree(&trigramToks_file1);
    destroyTree(&trigramToks_file2);
    /*Code for trigram Ends*/

    /*Print the final result along with filenames*/

    /*
     *   Calculate the similarity for bigram as well as trigram tokens and display their
     *    average for more accuarate results
     */

    double file1_to_file2_similarity = (Jaccard_bigram_similarity_file1 + Jaccard_trigram_similarity_file1) / 2.0;
    double file2_to_file1_similarity = (Jaccard_bigram_similarity_file2 + Jaccard_trigram_similarity_file2) / 2.0;

    printf("The Similarity %% between %s and %s is %.2lf%%\n", argv[1], argv[2], (file1_to_file2_similarity * 100));
    printf("The Similarity %% between %s and %s is %.2lf%% \n", argv[2], argv[1], (file2_to_file1_similarity * 100));
    return 0;
}
