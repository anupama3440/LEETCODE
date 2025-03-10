struct TreeNode* buildTree(int* nums, int left, int right) {
    if (left > right) {
        return NULL;
    }

    int mid = left + (right - left) / 2;
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (!node) {
        return NULL;
    }

    node->val = nums[mid];
    node->left = buildTree(nums, left, mid - 1);
    node->right = buildTree(nums, mid + 1, right);

    return node;
}
struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    return buildTree(nums, 0, numsSize - 1);
}
