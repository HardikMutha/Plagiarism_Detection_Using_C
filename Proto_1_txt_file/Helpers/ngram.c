void getBigrams(tree *t, list words, int *total_bigrams_file);
void getTrigrams(tree *t, list words, int *total_trigrams_file);

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
