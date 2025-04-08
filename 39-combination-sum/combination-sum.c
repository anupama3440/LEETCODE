/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#define MAX_COMBINATIONS 150
#define MAX_COMBINATION_LENGTH 40

void backtrack(int* candidates, int candidatesSize, int target, int* currComb, int currSize,
               int start, int** results, int* returnSize, int** returnColumnSizes) {
    if (target == 0) {
        results[*returnSize] = (int*)malloc(sizeof(int) * currSize);
        (*returnColumnSizes)[*returnSize] = currSize;
        for (int i = 0; i < currSize; ++i) {
            results[*returnSize][i] = currComb[i];
        }
        (*returnSize)++;
        return;
    }

    for (int i = start; i < candidatesSize; ++i) {
        if (candidates[i] <= target) {
            currComb[currSize] = candidates[i];
            backtrack(candidates, candidatesSize, target - candidates[i], currComb, currSize + 1, i,
                      results, returnSize, returnColumnSizes);
        }
    }
}

int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;

    int** results = (int**)malloc(sizeof(int*) * MAX_COMBINATIONS);
    *returnColumnSizes = (int*)malloc(sizeof(int) * MAX_COMBINATIONS);
    int* currComb = (int*)malloc(sizeof(int) * MAX_COMBINATION_LENGTH);

    backtrack(candidates, candidatesSize, target, currComb, 0, 0, results, returnSize, returnColumnSizes);

    free(currComb);
    return results;
}