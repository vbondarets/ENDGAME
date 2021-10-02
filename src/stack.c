#include "header.h"
t_stack new_stack(int capacity, int type_size) {
    t_stack stack;
    stack.data = malloc(capacity * type_size);
    stack.capacity = capacity;
    stack.type_size = type_size;
    stack.size = 0;
    return stack;
}

void stack_push(t_stack* stack, const void* data) { 
    if(stack->size >= stack->capacity) {
        printf("Stack overflow\n");
    }
    memcpy((char*)stack->data + (stack->size * stack->type_size), data, stack->type_size);
    stack->size++;
}
 
void* stack_pop(t_stack* stack) {
    stack->size--;
    return &(((char*)stack->data)[stack->size * stack->type_size]);
}

void stack_clear(t_stack* stack) {
    while(stack->size) {
        stack_pop(stack);
    }
}

