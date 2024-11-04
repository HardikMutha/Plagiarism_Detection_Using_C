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

int compare_slls(list *l1, list *l2) {
    listnode *temp1 = l1->head;
    listnode *temp2 = l2->head;
    int match = 0;
    /* int extra = 2; */
    while(temp1 != NULL && temp2 != NULL) {
        if(temp1->type == temp2->type) {
            match++;
            /* debug1 */
            /* if(temp1->type != 9 && strcmp(temp1->val, temp2->val) == 0) */
            /*     match += extra; */
        }
        /* else */
        /*     break; */
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    /* printf("match: %d\n", match); */
    return match;
}

int get_list_length(list l) {
    listnode *temp = l.head;
    int length = 0;
    while(temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
}

int compare_dlls(DLL *l1, DLL *l2) {
    nodeDLL *temp1 = l1->front;
    nodeDLL *temp2 = l2->front;
    printf("lengths: %d %d\n", l1->DLL_length, l2->DLL_length);
    int max_match = 0;
    int match = 0;
    int matched_lines = 0;
    /* int running = 0; */
    while(temp1 != NULL) {
        int len = get_list_length(*(temp1->l));
        while(temp2 != NULL) {
            match = compare_slls(temp1->l, temp2->l);
            if(match >= max_match) {
                max_match = match;
                if(max_match == len) {
                    matched_lines++;    
                    break;
                }
                /* running++; */
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
        temp2 = l2->front;
        max_match = 0;
    }
    return matched_lines;
}


int compare_files(DLL *file1, DLL *file2) {
    int matched_lines = 0;
    matched_lines = compare_dlls(file1, file2);
    return matched_lines;
}

