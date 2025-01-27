void backtrack(int* nums, int numsSize, int start, int* path, int pathSize, int** result, int* returnSize, int** returnColumnSizes) 
{
    result[*returnSize] = (int*)malloc(pathSize * sizeof(int));
    memcpy(result[*returnSize], path, pathSize * sizeof(int));
    (*returnColumnSizes)[*returnSize] = pathSize;
    (*returnSize)++;
    
    for (int i = start; i < numsSize; i++) 
    {
        path[pathSize] = nums[i];
        backtrack(nums, numsSize, i + 1, path, pathSize + 1, result, returnSize, returnColumnSizes);
    }
}

int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) 
{
    int totalSubsets = 1 << numsSize;
    int** result = (int**)malloc(totalSubsets * sizeof(int*));
    *returnColumnSizes = (int*)malloc(totalSubsets * sizeof(int));
    int* path = (int*)malloc(numsSize * sizeof(int));
    *returnSize = 0;
    backtrack(nums, numsSize, 0, path, 0, result, returnSize, returnColumnSizes);
    free(path);
    return result;
}