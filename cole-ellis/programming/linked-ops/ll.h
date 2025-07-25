#include <stdint.h>

#pragma once

// Linked List node
typedef struct Node {
  uint8_t value;
  struct Node *next;
} Node;

// Make new node
Node *makeNode(uint8_t value);

// Add node to front
Node *add2front(uint8_t value, Node *LL);

// Add node to back
Node *add2back(uint8_t value, Node *LL);

// Insert node at index
Node *insertNode(uint8_t value, uint16_t index, Node* LL);

// Remove last node in LL
Node *removeLastNode(Node *LL);

// Remove first node in LL
Node *removeFirstNode(Node *LL);

// Remove node at index
Node *popNode(uint16_t index, Node* LL);

// Print nodes in LL
void printLL(Node* LL);
