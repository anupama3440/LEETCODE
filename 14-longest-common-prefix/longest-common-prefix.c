
char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize == 0) return "";
    for (int j = 0; strs[0][j] != '\0'; j++) {
        char currentChar = strs[0][j];
        for (int i = 1; i < strsSize; i++) {
            if (strs[i][j] == '\0' || strs[i][j] != currentChar) {
                char* result = (char*)malloc((j + 1) * sizeof(char));
                strncpy(result, strs[0], j);
                result[j] = '\0';
                return result;
            }
        }
    }
    return strs[0];
}