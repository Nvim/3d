#ifndef STACK_H

#define STACK_H
#include "header.h"

typedef struct triStackNode {
  triangle tri;
  struct triStackNode *next;
} triStackNode;

typedef struct {
  u32 count;
  triStackNode *top;
} triStack;

/* stack.c : */
void init_stack(triStack *stack);
int stack_empty(const triStack *stack);
void stack_push(triStack *stack, const triangle tri);
triangle stack_pop(triStack *stack);
triangle stack_peek(const triStack *stack);

#endif // !STACK_H
