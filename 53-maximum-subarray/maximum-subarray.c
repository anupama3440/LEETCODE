int maxSubArray(int* nums, int numsSize) {
    int max_curr = nums[0];
    int max = nums[0];
    for (int i = 1; i < numsSize; i++) {
        max_curr = (nums[i] > (max_curr + nums[i])) ? nums[i] : (max_curr + nums[i]);
        max = (max > max_curr) ? max : max_curr;
    }
    return max;
}