int* grayCode(int n, int* returnSize) {
    *returnSize = 1 << n; 
    int* result = (int*)malloc((*returnSize) * sizeof(int));
    if (result == NULL) {
        return NULL; 
    }

    for (int i = 0; i < *returnSize; i++) {
        result[i] = i ^ (i >> 1);
    }

    return result;
}