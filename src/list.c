#include "../include/header.h"

void init_stack(triStack *stack) { stack->top = NULL; }

int stack_empty(triStack *stack) { return (stack->top == NULL); }

void stack_push(triStack *stack, triangle tri) {
  // Allouer la mémoire pour un nouvel élément
  triStackNode *new = (triStackNode *)malloc(sizeof(triStackNode));

  // Vérifier si l'allocation a réussi
  if (new == NULL) {
    fprintf(stderr, "Erreur d'allocation de mémoire\n");
    exit(EXIT_FAILURE);
  }

  // Assigner la valeur et mettre à jour le pointeur next
  new->tri = tri;
  new->next = stack->top;

  // Mettre à jour le pointeur top de la pile
  stack->top = new;
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

  // Libérer la mémoire de l'ancien élément
  free(temp);

  // Retourner le triangle retiré
  return t;
}
