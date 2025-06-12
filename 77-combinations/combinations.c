/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
void backtrack(int n, int k, int start, int* current, int** result, int* returnSize, int** returnColumnSizes, int depth) {
    if (depth == k) {
        result[*returnSize] = (int*)malloc(sizeof(int) * k);
        (*returnColumnSizes)[*returnSize] = k;
        for (int i = 0; i < k; i++) {
            result[*returnSize][i] = current[i];
        }
        (*returnSize)++;
        return;
    }

    for (int i = start; i <= n - (k - depth) + 1; i++) {
        current[depth] = i;
        backtrack(n, k, i + 1, current, result, returnSize, returnColumnSizes, depth + 1);
    }
}

int** combine(int n, int k, int* returnSize, int** returnColumnSizes) {
    int maxCombinations = 1;
    for (int i = 0; i < k; i++) {
        maxCombinations *= (n - i);
        maxCombinations /= (i + 1);
    }

    int** result = (int**)malloc(sizeof(int*) * maxCombinations);
    *returnColumnSizes = (int*)malloc(sizeof(int) * maxCombinations);
    int* current = (int*)malloc(sizeof(int) * k);
    *returnSize = 0;

    backtrack(n, k, 1, current, result, returnSize, returnColumnSizes, 0);

    free(current);
    return result;
}