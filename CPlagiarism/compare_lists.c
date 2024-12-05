#define debug1 printf("here1\n");
#define debug2 printf("here2\n");
#define max(A, B) (A) > (B) ? (A) : (B)

/*
    This function accepts the token type and return 1 if the value of the token should be checked
    else returns 0
    types to be checked are:
        - Delimiters
        - Special Characters
        - Logical Operators
        - Arithmetic Operators
        - Relational Operators
        - Keywords
*/
int should_value_be_checked(TokenType t)
{
    if (t == TOKEN_DELIM || t == TOKEN_SPCHAR || t == TOKEN_LOGICAL || t == TOKEN_ARITHMATIX || t == TOKEN_RELATIONAL || t == TOKEN_KEYWORD)
        return 1;
    return 0;
}

/*
    This function accepts two singly linked lists and returns the similarity score
    by comparing the nodes of the two lists
    If the type of the two nodes is same, then the value of the nodes is compared
    If the value of the nodes is same, then the score is incremented
    The final score is calculated by dividing the matched tokens by the length of the first list
    The final score is returned
*/
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

/*
    This function accepts two doubly linked lists and returns the sum of the maximum match of the two lists
    The function finds the maximum match of all the nodes (lines) of the first list
    with respect to the second list
    The function calculates the sum of maximum matched lines (lines with match >= 0.8)
*/
double compare_dlls(DLL *l1, DLL *l2)
{
    nodeDLL *temp1 = l1->front;
    nodeDLL *temp2 = l2->front;
    double match = 0.0;
    double max_match = 0.0;
    double sum_max_match_primary = 0.0;
    while (temp1 != NULL)
    {
        // loop through all the nodes of the second list to find the maximum match
        // with respect to the current node of the first list
        while (temp2 != NULL)
        {
            // if the node in the second list is already matched 
            // then skip the node
            if (temp2->flag == 1)
            {
                temp2 = temp2->next;
                continue;
            }
            // compare the two singly linked lists stored in the nodes
            match = compare_slls(temp1->l, temp2->l);
            // if the match is equal to 1, then set the flag of the node in the second list to 1
            if (match == 1) {
                temp2->flag = 1;
            }
            max_match = max(match, max_match);
            temp2 = temp2->next;
        }
        // update the max_match value of the current node of the first list
        temp1->max_match = max_match;
        // if the max_match value is greater than or equal to 0.8, then add the value to the sum
        if (max_match >= 0.8f)
            sum_max_match_primary += max_match;
        temp1 = temp1->next;
        temp2 = l2->front;
        max_match = 0.0;
    }
    return sum_max_match_primary;
}

/*
    This function accepts a doubly linked list and resets the flags and 
    max_match values of all the nodes in the list
*/
void reset_flags_max_match_values(DLL *l1)
{
    nodeDLL *temp = l1->front;
    while (temp)
    {
        temp->flag = 0;
        temp->max_match = 0.0;
        temp = temp->next;
    }
    return;
}

/*
    This function accepts a doubly linked list and the sum of the maximum matched lines
    The function calculates and returns the final score by dividing the sum by the length of the list
*/
double get_final_ans(DLL *l, double sum)
{
    return (double)(sum / (l->DLL_length * 1.0));
}

/*
    This function accepts two doubly linked lists
    The function calls the compare_dlls function to find the maximum matched 
    nodes (lines of the two files)
    The function returns the sum of the maximum matched lines
*/
void compare_files(DLL *file1, DLL *file2, double *final_ans1, double *final_ans2)
{
    double matched_lines = 0;
    matched_lines = compare_dlls(file1, file2);
    *final_ans1 = get_final_ans(file1, matched_lines);
    matched_lines = compare_dlls(file2, file1);
    *final_ans2 = get_final_ans(file2, matched_lines);
    reset_flags_max_match_values(file1);
    reset_flags_max_match_values(file2);
    return;
}