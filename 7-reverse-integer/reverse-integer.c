int reverse(int x) {
    int reversed = 0;

    while (x != 0) {
        int remainder = x % 10;
        if (reversed > (INT_MAX / 10) || (reversed == INT_MAX / 10 && remainder > 7)) {
            return 0; 
        }
        if (reversed < (INT_MIN / 10) || (reversed == INT_MIN / 10 && remainder < -8)) {
            return 0; 
        }

        reversed = reversed * 10 + remainder;
        x /= 10;
    }

    return reversed;
}