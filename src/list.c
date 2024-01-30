#include "../include/header.h"

void init_stack(triStack *stack) {
  stack->top = NULL;
  stack->count = 0;
}

int stack_empty(triStack *stack) { return (stack->top == NULL); }

void stack_push(triStack *stack, triangle tri) {
  // Allouer la mémoire pour un nouvel élément
  triStackNode *new = (triStackNode *)malloc(sizeof(triStackNode));

  if (new == NULL) {
    fprintf(stderr, "Erreur d'allocation de mémoire\n");
    exit(EXIT_FAILURE);
  }

  new->tri = tri;
  new->next = stack->top;
  stack->top = new;
  stack->count++;
}

triangle stack_pop(triStack *stack) {
  if (stack_empty(stack)) {
    fprintf(stderr, "La pile est vide\n");
    exit(EXIT_FAILURE);
  }

  // Récupérer le triangle en haut de la pile
  triangle t = stack->top->tri;

  // Mettre à jour le pointeur top pour pointer vers le prochain élément
  triStackNode *temp = stack->top;
  stack->top = stack->top->next;
  stack->count--;

  // Libérer la mémoire de l'ancien élément
  free(temp);

  // Retourner le triangle retiré
  return t;
}

// peek top
triangle stack_peek(triStack *stack) {
  if (stack_empty(stack)) {
    fprintf(stderr, "La pile est vide\n");
    exit(EXIT_FAILURE);
  }

  // Retourner le triangle en haut de la pile
  return stack->top->tri;
}
