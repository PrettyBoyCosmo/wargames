// Title:       linked-ops.h
// Description: Linked ops header file
// Author:      bluecosmo

#pragma once

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

// Linked list node
typedef struct LLNode {
  uint8_t value;
  struct LLNode *next;
} LLNode;

// Make new node for linked list
LLNode *newNode(uint8_t value);

// [0] Add to back
LLNode *addToBack(uint8_t value, LLNode *head);

// [1] Add linked list node to front
LLNode *addToFront(uint8_t value, LLNode *head);

// [2] Insert node at specific index
LLNode *insertAt(uint8_t value, uint16_t index, LLNode *head);

// [3] Remove node from end of linked list
LLNode *removeEnd(LLNode *head);

// [4] Remove node from front of linked list
LLNode *removeFront(LLNode *head);

// [5] Remove node from specific index
LLNode *removeAt(uint16_t index, LLNode *head);

// Print linked list nodes
void printLL(LLNode *head);

// Print flag
void printFlag(LLNode *head);
