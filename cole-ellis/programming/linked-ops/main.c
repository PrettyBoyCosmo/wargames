// Title:       main.c
// Description: Linked ops solution
// Author:      bluecosmo

#include <stdio.h>
#include <stdlib.h>

#include "linked-ops.h"

int main(void) {

  FILE *fp = fopen("./data.bin", "rb");
  if (fp == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  uint8_t opcode;
  uint8_t character;
  uint16_t index;
  LLNode *ll = NULL;

  while (fread(&opcode, sizeof(uint8_t), 1, fp) == 1) {

    if (opcode == 0) {
      fread(&character, sizeof(uint8_t), 1, fp);
      ll = addToBack(character, ll);
    }

    else if (opcode == 1) {
      fread(&character, sizeof(uint8_t), 1, fp);
      ll = addToFront(character, ll);
    }

    else if (opcode == 2) {
      fread(&index, sizeof(uint16_t), 1, fp);
      fread(&character, sizeof(uint8_t), 1, fp);
      ll = insertAt(character, index, ll);
    }

    else if (opcode == 3) {
      ll = removeEnd(ll);
    }

    else if (opcode == 4) {
      ll = removeFront(ll);
    }

    else if (opcode == 5) {
      fread(&index, sizeof(uint16_t), 1, fp);
      ll = removeAt(index, ll);
    }

    else {
      printf("[!] ERROR: Opocode 0x%02x does not exist.", opcode);
    }

    printf("Index: 0x%lx\n", ftell(fp));
    printf("OP: 0x%02x\n", opcode);
    printf("CH: 0x%02x (%c)\n", character, character);
    printf("IX: 0x%02x\n", index);
    printFlag(ll);
  }

  printFlag(ll);
  return EXIT_SUCCESS;
}
