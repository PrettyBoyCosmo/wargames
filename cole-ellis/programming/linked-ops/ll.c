#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "ll.h"

// Make new node
Node *makeNode(uint8_t value) {
  Node *newNode = (Node *) malloc(sizeof(Node));
  newNode->value = value;
  newNode->next = NULL;
  return newNode;
}

// Add node to front
Node *add2front(uint8_t value, Node *head) {
  Node* newNode = makeNode(value);
  newNode->next = head;
  return newNode;
}

// Add node to back
Node *add2back(uint8_t value, Node *head) {
  if (head == NULL) {
    Node *newNode = makeNode(value);
    return newNode;
  }
  head->next = add2back(value, head->next);
  return head;
}

Node *insertNode(uint8_t value, uint16_t index, Node* LL) {

    // empty list or insert at head
    if (LL == NULL || index == 0)
        return add2front(value, LL);

    Node *head = LL;
    Node *prev = NULL;
    uint16_t i = 0;

    // walk until either we hit the desired index, or run out of nodes
    while (LL != NULL && i < index) {
        prev = LL;
        LL   = LL->next;
        i++;
    }

    // now either:
    //  - i == index  ⇒ LL is the node currently at 'index', or NULL if we walked off the end
    //  - i  < index ⇒ we ran out of list before reaching index

    Node *newNode = makeNode(value);

    if (i == index) {
        // insert before LL (which may be NULL if index == length)
        prev->next   = newNode;
        newNode->next = LL;
    } else {
        // index > length  ⇒ just append to the tail
        // note: prev is the last node
        prev->next    = newNode;
        newNode->next = NULL;
    }

    return head;
}

// Remove last node in LL
Node *removeLastNode(Node *LL) {

  if (LL == NULL)
    return NULL;

  if (LL->next == NULL) {
    free(LL);
    return NULL;
  }

  Node *head = LL;
  Node *prevNode = LL;

  while (LL->next != NULL) {
    prevNode = LL;
    LL = LL->next;
  }

  free(LL);
  prevNode->next = NULL;
  return head;
}

// Remove first node in LL
Node *removeFirstNode(Node *LL) {
  if (LL == NULL) return NULL;
  Node *remainingLL = LL->next;
  free(LL);
  return remainingLL;
}

// Remove node at index
Node *popNode(uint16_t index, Node* LL) {

  if (LL == NULL)
    return NULL;

  if (index == 0) {
    Node* head = LL->next;
    free(LL);
    return head;
  }

  Node* head = LL;
  Node* prevNode = LL;
  LL = LL->next;

  for (uint16_t i = 1; LL != NULL; i++) {

    if (i == index) {
      prevNode->next = LL->next;
      free(LL);
      return head;
    }
    prevNode = LL;
    LL = LL->next;
  }
  return head;
}

// Print nodes in LL
void printLL(Node* LL) {
  printf("flag{");
  while (LL != NULL) {
    printf("%c", LL->value);
    LL = LL->next;
  }
  puts("}");
  return;
}
