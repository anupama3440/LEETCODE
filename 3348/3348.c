#define MAX_LEN 1000000
#define MAX_PRIMES 4
#define MAX_DIGITS 10

struct PrimeCount {
    int count[MAX_PRIMES];
};

struct FactorCount {
    int count[MAX_DIGITS];
};

struct PrimeCountResult {
    struct PrimeCount count;
    bool isDivisible;
};

const int kFactorCounts[10][MAX_PRIMES] = {
    {0, 0, 0, 0}, 
    {0, 0, 0, 0}, 
    {1, 0, 0, 0}, 
    {0, 1, 0, 0},
    {2, 0, 0, 0}, 
    {0, 0, 1, 0}, 
    {1, 1, 0, 0},  
    {0, 0, 0, 1}, 
    {3, 0, 0, 0}, 
    {0, 2, 0, 0}  
};

struct PrimeCount getPrimeCountFromString(const char* num) {
    struct PrimeCount count = {{0}};
    int len = strlen(num);
    for (int i = 0; i < len; i++) {
        int digit = num[i] - '0';
        for (int j = 0; j < MAX_PRIMES; j++) {
            count.count[j] += kFactorCounts[digit][j];
        }
    }
    return count;
}

struct PrimeCountResult getPrimeCount(long long t) {
    struct PrimeCountResult result;
    memset(result.count.count, 0, sizeof(result.count.count));
    result.isDivisible = true;

    int primes[] = {2, 3, 5, 7};
    
    for (int i = 0; i < MAX_PRIMES; i++) {
        while (t % primes[i] == 0) {
            t /= primes[i];
            result.count.count[i]++;
        }
        if (t == 1) break;
    }

    result.isDivisible = (t == 1);
    return result;
}

struct FactorCount getFactorCount(struct PrimeCount count) {
    struct FactorCount result = {{0}};
    
    int count8 = count.count[0] / 3;
    int remaining2 = count.count[0] % 3;
    int count9 = count.count[1] / 2;
    int count3 = count.count[1] % 2;
    int count4 = remaining2 / 2;
    int count2 = remaining2 % 2;
    int count6 = 0;

    if (count2 == 1 && count3 == 1) {
        count2 = 0;
        count3 = 0;
        count6 = 1;
    }
    if (count3 == 1 && count4 == 1) {
        count2 = 1;
        count6 = 1;
        count3 = 0;
        count4 = 0;
    }

    result.count[2] = count2;
    result.count[3] = count3;
    result.count[4] = count4;
    result.count[5] = count.count[2];
    result.count[6] = count6;
    result.count[7] = count.count[3];
    result.count[8] = count8;
    result.count[9] = count9;
    
    return result;
}

int sumValues(struct FactorCount count) {
    int sum = 0;
    for (int i = 0; i < MAX_DIGITS; i++) {
        sum += count.count[i];
    }
    return sum;
}

void constructNumber(struct FactorCount factors, char* result) {
    int pos = 0;
    for (int digit = 2; digit < MAX_DIGITS; digit++) {
        for (int j = 0; j < factors.count[digit]; j++) {
            result[pos++] = digit + '0';
        }
    }
    result[pos] = '\0';
}

bool isSubset(struct PrimeCount a, struct PrimeCount b) {
    for (int i = 0; i < MAX_PRIMES; i++) {
        if (b.count[i] < a.count[i]) return false;
    }
    return true;
}

struct PrimeCount subtract(struct PrimeCount a, struct PrimeCount b) {
    struct PrimeCount result = {{0}};
    for (int i = 0; i < MAX_PRIMES; i++) {
        if (a.count[i] < b.count[i]) {
            result.count[i] = 0;
        } else {
            result.count[i] = a.count[i] - b.count[i];
        }
    }
    return result;
}

void fillResult(char* result, const char* prefix, int prefixLen, 
               int biggerDigit, int fillOnes, struct FactorCount factors) {
    int pos = 0;
    int maxLen = MAX_LEN - 1;
    for (int i = 0; i < prefixLen && pos < maxLen; i++) {
        result[pos++] = prefix[i];
    }
    if (pos < maxLen) {
        result[pos++] = biggerDigit + '0';
    }
    for (int i = 0; i < fillOnes && pos < maxLen; i++) {
        result[pos++] = '1';
    }
    for (int digit = 2; digit < MAX_DIGITS && pos < maxLen; digit++) {
        for (int j = 0; j < factors.count[digit] && pos < maxLen; j++) {
            result[pos++] = digit + '0';
        }
    }
    
    result[pos] = '\0';
}

char* smallestNumber(const char* num, long long t) {
    char* result = (char*)malloc(MAX_LEN);
    if (!result) return NULL;

    struct PrimeCountResult primeResult = getPrimeCount(t);
    if (!primeResult.isDivisible) {
        strcpy(result, "-1");
        return result;
    }

    struct FactorCount factorCount = getFactorCount(primeResult.count);
    int totalFactors = sumValues(factorCount);
    int numLen = strlen(num);

    if (totalFactors > numLen) {
        constructNumber(factorCount, result);
        return result;
    }

    struct PrimeCount primeCountPrefix = getPrimeCountFromString(num);
    int firstZeroIndex = -1;

    for (int i = 0; i < numLen; i++) {
        if (num[i] == '0') {
            firstZeroIndex = i;
            break;
        }
    }

    if (firstZeroIndex == -1) {
        firstZeroIndex = numLen;
        if (isSubset(primeResult.count, primeCountPrefix)) {
            strcpy(result, num);
            return result;
        }
    }

    for (int i = numLen - 1; i >= 0; i--) {
        int d = num[i] - '0';
        struct PrimeCount tempCount = {{0}};
        for (int j = 0; j < MAX_PRIMES; j++) {
            tempCount.count[j] = kFactorCounts[d][j];
        }
        primeCountPrefix = subtract(primeCountPrefix, tempCount);

        int spaceAfterThisDigit = numLen - 1 - i;

        if (i > firstZeroIndex) continue;

        for (int biggerDigit = d + 1; biggerDigit < 10; biggerDigit++) {
            struct PrimeCount subtracted = subtract(
                subtract(primeResult.count, primeCountPrefix),
                *(struct PrimeCount*)kFactorCounts[biggerDigit]
            );

            struct FactorCount factorsAfterReplacement = getFactorCount(subtracted);
            int sumFactors = sumValues(factorsAfterReplacement);

            if (sumFactors <= spaceAfterThisDigit) {
                int fillOnes = spaceAfterThisDigit - sumFactors;
                fillResult(result, num, i, biggerDigit, fillOnes, factorsAfterReplacement);
                return result;
            }
        }
    }

    struct FactorCount factorsAfterExtension = getFactorCount(primeResult.count);
    int sumFactors = sumValues(factorsAfterExtension);
    int numOnes = numLen + 1 - sumFactors;

    int pos = 0;
    for (int i = 0; i < numOnes; i++) {
        result[pos++] = '1';
    }

    char temp[MAX_LEN];
    constructNumber(factorsAfterExtension, temp);
    strcpy(result + pos, temp);

    return result;
}
