// Title:       linked-ops.c
// Description: Linked ops implementation file
// Author:      bluecosmo

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "linked-ops.h"

// Make new node for linked list
LLNode *newNode(uint8_t value) {
  LLNode *new_node = (LLNode*) malloc(sizeof(LLNode));
  if (new_node != NULL) {
    new_node->value = value;
    new_node->next = NULL;
  }
  return new_node;
}

// [0] Add to back
LLNode *addToBack(uint8_t value, LLNode *head) {

  LLNode *new_node = newNode(value);
  if (head == NULL) return new_node;

  LLNode *curr = head;
  while(curr->next != NULL) { curr = curr->next; }
  curr->next = new_node;
  return head;
}

// [1] Add linked list node to front
LLNode *addToFront(uint8_t value, LLNode *head) {
  LLNode *new_node = newNode(value);
  if (head == NULL) return new_node;
  new_node->next = head;
  return new_node;
}

// [2] Insert node at specific index
LLNode *insertAt(uint8_t value, uint16_t index, LLNode *head) {

  LLNode *new_node = newNode(value);
  if (head == NULL) return new_node;
  if (index == 0) return addToFront(value, head);

  uint16_t i = 0;
  LLNode *curr = head;
  LLNode *prev = head;
  while (curr != NULL) {

    if (i == index) {
      prev->next = new_node;
      new_node->next = curr;
      return head;
    }

    prev = curr;
    curr = curr->next;
    i++;
  }
  return addToBack(value, head);
  /*prev->next = new_node;*/
  /*return head;*/
}

// [3] Remove node from end of linked list
LLNode *removeEnd(LLNode *head) {
  if (head == NULL) return NULL;
  if (head->next == NULL) {
    free(head);
    return NULL;
  }
  LLNode *curr = head;
  LLNode *prev = head;
  while (curr->next != NULL) {
    prev = curr;
    curr = curr->next;
  }
  free(curr);
  prev->next = NULL;
  return head;
}

// [4] Remove node from front of linked list
LLNode *removeFront(LLNode *head) {
  if (head == NULL) return NULL;
  LLNode *new_head = head->next;
  free(head);
  return new_head;
}

// [5] Remove node from specific index
// NOTE: removes last node if out of bounds
LLNode *removeAt(uint16_t index, LLNode *head) {
  if (head == NULL) return NULL;
  if (index == 0) return removeFront(head);

  uint16_t i = 0;
  LLNode *curr = head;
  LLNode *prev = head;

  while (curr->next != NULL) {
    if (i == index) {
      prev->next = curr->next;
      free(curr);
      return head;
    }

    prev = curr;
    curr = curr->next;
    i++;
  }

  return removeEnd(head);
}

// Print linked list nodes
void printLL(LLNode *head) {
  LLNode *curr = head;
  while (curr != NULL) {
    printf("%02x -> ", curr->value);
    curr = curr->next;
  }
  printf("NULL\n");
  return;
}

// Print flag
void printFlag(LLNode *head) {
  LLNode *curr = head;
  printf("flag{");
  while (curr != NULL) {
    printf("%c", curr->value);
    curr = curr->next;
  }
  printf("}\n");
  return;
}
