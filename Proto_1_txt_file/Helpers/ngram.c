void getBigrams(tree *t, list words, int *total_bigrams_file);
void getTrigrams(tree *t, list words, int *total_trigrams_file);

/*
    This function takes in a list of tokenized words.
    Then the tokens are combined to form bigrams.
    These bigrams are then inserted into the binary Search Tree.
    The insertion operation takes place in O(logn) time.
    The total number of bigrams in the file is also calculated.
*/

void getBigrams(tree *t, list words, int *total_bigrams_file)
{
    char *token;
    listnode *p = words.head;
    for (int j = 0; j < words.len - 1; j++)
    {
        token = (char *)malloc(strlen(p->val) + strlen(p->next->val) + 1); // Allocate Space Equal to the sum of lengths of the two words.
        strcpy(token, p->val);                                             // Copy the first word of the bigram.
        strcat(token, p->next->val);                                       // Concat the second word of the bigram to generate a bigram.
        int x = insertValue(t, token);                                     // insertFunction from BST ADT.
        if (x == 1)
            (*total_bigrams_file)++;
        free(token);
        p = p->next;
    }
    return;
}

/*
    This function takes in a list of tokenized words.
    Then the tokens are combined to form trigrams.
    These trigrams are then inserted into the binary Search Tree.
    The insertion operation takes place in O(logn) time.
    The total number of trigrams in the file is also calculated.
*/

void getTrigrams(tree *t, list words, int *total_trigrams_file)
{
    char *token;
    listnode *p = words.head;
    for (int j = 0; j < words.len - 2; j++)
    {
        token = (char *)malloc(strlen(p->val) + strlen(p->next->val) + strlen(p->next->next->val) + 1); // Allocate Space Equal to the sum of lengths of the three words.
        strcpy(token, p->val);                                                                          // Copy the first word.
        strcat(token, p->next->val);                                                                    // Concatenate the second word.
        strcat(token, p->next->next->val);                                                              // Concatenate the third word.
        int x = insertValue(t, token);                                                                  // insertFunction from BST ADT.
        if (x == 1)
            (*total_trigrams_file)++;
        free(token);
        p = p->next;
    }
    return;
}
