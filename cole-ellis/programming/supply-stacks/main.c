// Title:       main.c
// Description: Supply Stacks Solution
// Author:      bluecosmo

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define NUM_OF_STACKS 9

typedef struct StackNode {
  uint8_t value;
  struct StackNode *next;
} StackNode;

StackNode *newNode(uint8_t value) {
  StackNode *new_node = (StackNode*) malloc(sizeof(StackNode));
  if (new_node) {
    new_node->value = value;
    new_node->next = NULL;
  }
  return new_node;
}

void push(uint8_t value, StackNode **top) {
  StackNode *new_node = newNode(value);
  new_node->next = *top;
  *top = new_node;
}

StackNode *pushBottom(uint8_t value, StackNode *top) {
  StackNode *new_node = newNode(value);
  if (top == NULL) { return new_node; }
  StackNode *curr = top;
  while (curr->next != NULL) { curr = curr->next; }
  curr->next = new_node;
  return top;
}

uint8_t peek(StackNode *top) { return top->value; }

void pop(StackNode **top) {
  StackNode *old_top = *top;
  *top = (*top)->next;
  free(old_top);
  return;
}

void move(uint8_t num_of_crates, StackNode **from_stack, StackNode **to_stack) {
  for (uint8_t i = 0; i < num_of_crates; i++) {
    uint8_t value = peek(*from_stack);
    pop(from_stack);
    push(value, to_stack);
  }
}

int main(void) {

  FILE *fp = fopen("./input.txt", "r");
  if (!fp) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  char *line_read = NULL;
  size_t line_length = 0;
  StackNode *stack_array[NUM_OF_STACKS] = {NULL};

  while (getline(&line_read, &line_length, fp) != EOF) {

    // Read in stacks to array of stacks
    if (line_read[0] == 'm') {

      // Read in instructions
      strtok(line_read, " "); // "move"
      uint8_t num_of_crates = atoi(strtok(NULL, " "));
      strtok(NULL, " "); // "from"
      uint8_t from_stack = atoi(strtok(NULL, " "));
      strtok(NULL, " "); // "to"
      uint8_t to_stack = atoi(strtok(NULL, " "));

      move(num_of_crates, &stack_array[from_stack - 1], &stack_array[to_stack - 1]);
    }

    else {
      for (uint8_t i = 1; i < strlen(line_read); i += 4) {
        uint8_t stack_array_idx = (i / 4) % NUM_OF_STACKS;
        if (line_read[i] != 0x20) {
          stack_array[stack_array_idx] = pushBottom(line_read[i], stack_array[stack_array_idx]);
          printf("%p:\tarray[%d]:\t %c\n", stack_array[stack_array_idx], stack_array_idx, line_read[i]);
        }
      }
      printf("\n");

    }
  }

  printf("Cosmo:\t flag{");
  for (uint8_t i = 0; i < NUM_OF_STACKS; i++) {
    printf("%c", peek(stack_array[i]));
  }
  printf("}\n");
  printf("Ellis:\t flag{ZBDRNPMVH}");


  return EXIT_SUCCESS;
}
