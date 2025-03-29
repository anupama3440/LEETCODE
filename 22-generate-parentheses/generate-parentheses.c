void backtrack(char** result, int* returnSize, char* current, int open, int close, int max, int index) {
    if (index == 2 * max) {
        current[index] = '\0'; // Ensure proper null termination
        result[*returnSize] = strdup(current); // Store a copy in result
        (*returnSize)++;
        return;
    }

    if (open < max) {
        current[index] = '(';
        backtrack(result, returnSize, current, open + 1, close, max, index + 1);
    }

    if (close < open) {
        current[index] = ')';
        backtrack(result, returnSize, current, open, close + 1, max, index + 1);
    }
}

char** generateParenthesis(int n, int* returnSize) {
    *returnSize = 0;
    int maxCombinations = 2000; // Increased to prevent overflow
    char** result = (char**)malloc(maxCombinations * sizeof(char*));
    if (!result) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    char* current = (char*)malloc(2 * n + 1);
    if (!current) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    backtrack(result, returnSize, current, 0, 0, n, 0);

    free(current);
    return result;
}

void freeResult(char** result, int returnSize) {
    for (int i = 0; i < returnSize; i++) {
        free(result[i]);
    }
    free(result);
}