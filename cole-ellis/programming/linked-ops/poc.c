// Title:       FILENAME.c
// Description: DESCRIPTION
// Author:      bluecosmo

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ll.h"

int main() {

  Node *LL = NULL;

  LL = add2back(1, LL);
  printLL(LL);

  LL = removeLastNode(LL);
  printLL(LL);

  return EXIT_SUCCESS;
}

