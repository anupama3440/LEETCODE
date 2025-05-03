char* countAndSay(int n) {
    if (n == 1) {
        char* base = (char*)malloc(2 * sizeof(char));
        base[0] = '1';
        base[1] = '\0';
        return base;
    }
    char* prev = countAndSay(n - 1);
    int len = strlen(prev);
    char* result = (char*)malloc(5000 * sizeof(char)); 
    int resIndex = 0;

    for (int i = 0; i < len;) {
        char digit = prev[i];
        int count = 1;
        while (i + count < len && prev[i + count] == digit) {
            count++;
        }
        resIndex += sprintf(result + resIndex, "%d%c", count, digit);
        i += count;
    }
    result[resIndex] = '\0';
    free(prev); 
    return result;
}