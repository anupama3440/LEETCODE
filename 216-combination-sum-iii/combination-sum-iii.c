void backtrack(int k, int n, int start, int* path, int pathSize, int** result, int* returnSize, int** returnColumnSizes) {
    if (k == 0 && n == 0) {
        result[*returnSize] = (int*)malloc(sizeof(int) * pathSize);
        for (int i = 0; i < pathSize; ++i) {
            result[*returnSize][i] = path[i];
        }
        (*returnColumnSizes)[*returnSize] = pathSize;
        (*returnSize)++;
        return;
    }
    if (k == 0 || n < 0) {
        return;
    }
    
    for (int i = start; i <= 9; ++i) {
        path[pathSize] = i;
        backtrack(k - 1, n - i, i + 1, path, pathSize + 1, result, returnSize, returnColumnSizes);
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum3(int k, int n, int* returnSize, int** returnColumnSizes) {
    int** result = (int**)malloc(sizeof(int*) * 200); // allocate enough space
    *returnColumnSizes = (int*)malloc(sizeof(int) * 200);
    int* path = (int*)malloc(sizeof(int) * k);

    *returnSize = 0;
    backtrack(k, n, 1, path, 0, result, returnSize, returnColumnSizes);

    free(path);
    return result;

}
