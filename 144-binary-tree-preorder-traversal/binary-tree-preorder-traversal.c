/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define MAX_NODES 101  // max number of nodes as per constraint

void preorder(struct TreeNode* root, int* result, int* idx) {
    if (root == NULL) return;

    result[(*idx)++] = root->val;
    preorder(root->left, result, idx);
    preorder(root->right, result, idx);
}

int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    int* result = (int*)malloc(sizeof(int) * MAX_NODES);
    int idx = 0;

    preorder(root, result, &idx);

    *returnSize = idx;
    return result;
}