/*
 *   get_intersection_of_tokens()
 *   -> This function takes in two BST(binary search trees) as argument
 *   -> It compares the value of each and every node in tree 1 and searches for it in the tree 2
 *   -> A global variable intersection_of_tokens keeps a track of common tokens
 *   -> If if finds a node with common value then intersection_of_tokens is incremented
 *   -> At the end we recieve the number of nodes in common between both the trees
 */

void get_intersection_of_tokens(tree t1, tree t2);
int intersection_of_tokens = 0;
void get_intersection_of_tokens(tree t1, tree t2)
{
    if (t1 == NULL)
        return;
    get_intersection_of_tokens(t1->left, t2);
    if (searchNode(t2, t1->val))
    {
        intersection_of_tokens++;
    }
    get_intersection_of_tokens(t1->right, t2);
    return;
}

/*
*   getJaccardSimScore()
*   This is defind based on Jaccard Similarity Score Technique
    Jaccard Simialarity Score Technique ->
        => This is based on the concept of union and intersection
            Union -> Total number of tokens in the source File
            Intersection -> Total number of tokens common between the target and source file
        => After Calculating the Union and Intersection, the similarity Score between the files is calculated as follows
                    %age similarity = (Intersection/Union)
    Similarity Score is returned
*/

double getJaccardSimScore(int intersection_count, int totalTokens)
{
    double ans = (intersection_count * 1.0) / totalTokens;
    return ans;
}
