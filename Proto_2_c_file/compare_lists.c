/*
 * Comparison of two files
 * comparing functions will be called through main file repeteadly to check for similarity
 *
 *   - functions:
 *     - compare files
 *     - compare dlls
 *     - compare slls
 *
 *  - compare files:
 *      - internally calls for function to compare the dlls keeping the count
 *        of similar dll headers
 *      - if whole sll matches, in dll head matched flag is set to 1
 *
 *  - compare dlls:
 *      - compares the dlls by comparing the headers and the slls
 *      - internally calls for function to compare the slls
 *      - the line number of maximum match is returned to set matched flag
 *
 *  - compare slls:
 *      - compares the slls by comparing the nodes
 *      - the line number of maximum match is returned to set matched flag
 *
 *
 *
 */
#define debug1 printf("here1\n");
#define debug2 printf("here2\n");
#define max(A, B) (A) > (B) ? (A) : (B)

int should_value_be_checked(TokenType t)
{
    if (t == TOKEN_DELIM || t == TOKEN_SPCHAR || t == TOKEN_LOGICAL || t == TOKEN_ARITHMATIX || t == TOKEN_RELATIONAL || t == TOKEN_KEYWORD)
        return 1;
    return 0;
}

double compare_slls(list *l1, list *l2)
{
    listnode *temp1 = l1->head;
    listnode *temp2 = l2->head;
    int len_list1 = l1->len;
    int matched_tokens = 0;
    while (temp1 && temp2)
    {
        if (temp1->type == temp2->type)
        {
            if (should_value_be_checked(temp1->type))
            {
                if (strcmp(temp1->val, temp2->val) == 0)
                    matched_tokens++;
            }
            else
                matched_tokens++;
        }
        else
            break;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    double score = matched_tokens * 1.0;
    if (len_list1 > 0)
        return (score / len_list1);
    else
        return 0.0;
}

double compare_dlls(DLL *l1, DLL *l2)
{
    nodeDLL *temp1 = l1->front;
    nodeDLL *temp2 = l2->front;
    // printf("%d\n", l1->DLL_length);
    double match = 0.0;
    double max_match = 0.0;
    double sum_max_match_primary = 0.0;
    while (temp1 != NULL)
    {
        /* traverse_SLL(*(temp1->l)); */
        while (temp2 != NULL)
        {
            match = compare_slls(temp1->l, temp2->l);
            max_match = max(match, max_match);
            if (temp2->max_match < match)
                temp2->max_match = match;
            temp2 = temp2->next;
        }
        /* printf("%.2lf\n", max_match); */
        temp1->max_match = max_match;
        if (max_match >= 0.8f)
            sum_max_match_primary += max_match;
        temp1 = temp1->next;
        temp2 = l2->front;
        max_match = 0.0;
    }
    return sum_max_match_primary;
}

double compare_files(DLL *file1, DLL *file2)
{
    double matched_lines = 0;
    matched_lines = compare_dlls(file1, file2);
    return matched_lines;
}

double get_final_ans(DLL *l, double sum)
{
    return (sum / (l->DLL_length * 1.0));
}
