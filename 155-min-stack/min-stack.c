

typedef struct {
    int *stack;
    int *minStack;
    int topIndex;
    int minTopIndex;
    int capacity;
} MinStack;

MinStack* minStackCreate() {
    MinStack* obj = (MinStack*)malloc(sizeof(MinStack));
    obj->capacity = 10000;
    obj->stack = (int*)malloc(obj->capacity * sizeof(int));
    obj->minStack = (int*)malloc(obj->capacity * sizeof(int));
    obj->topIndex = -1;
    obj->minTopIndex = -1;
    return obj;
}

void minStackPush(MinStack* obj, int val) {
    if (obj->topIndex + 1 >= obj->capacity) {
        obj->capacity *= 2;
        obj->stack = (int*)realloc(obj->stack, obj->capacity * sizeof(int));
        obj->minStack = (int*)realloc(obj->minStack, obj->capacity * sizeof(int));
    }
    obj->stack[++obj->topIndex] = val;
    if (obj->minTopIndex == -1 || val <= obj->minStack[obj->minTopIndex]) {
        obj->minStack[++obj->minTopIndex] = val;
    }
}

void minStackPop(MinStack* obj) {
    if (obj->topIndex == -1) return;
    int poppedValue = obj->stack[obj->topIndex--];
    if (poppedValue == obj->minStack[obj->minTopIndex]) {
        obj->minTopIndex--;
    }
}

int minStackTop(MinStack* obj) {
    if (obj->topIndex == -1) return INT_MIN;
    return obj->stack[obj->topIndex];
}

int minStackGetMin(MinStack* obj) {
    if (obj->minTopIndex == -1) return INT_MIN;
    return obj->minStack[obj->minTopIndex];
}

void minStackFree(MinStack* obj) {
    free(obj->stack);
    free(obj->minStack);
    free(obj);
}