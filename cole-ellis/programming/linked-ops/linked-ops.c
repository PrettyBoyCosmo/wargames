// Title:       linked-ops.c
// Description: Cole Ellis serialization challenge
// Author:      bluecosmo

// flag{TjWc9AY)')G\A.Bf=N3pHP9Ej=3@M|ly4M;8KJOJgIT/ch8e}

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "ll.h"

int readByte(void *buffer, size_t size, FILE *fp) {
    if (fread(buffer, size, 1, fp) == 0) {
      perror("fread");
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main() {

  // Attempt to open data file
  FILE *fp = fopen("./data.bin", "rb");
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  Node* LL = NULL;
  uint8_t opcode, arg2;
  uint16_t arg1;

  // Read and execute opcodes
  puts("[*] Reading opcode...");
  while (readByte((uint8_t *)&opcode, sizeof(uint8_t), fp) != EXIT_FAILURE) {
    printf("[+] Opcode found: %d\n", (int) opcode);

    // Add to back
    if (opcode == 0) {
      readByte((uint8_t *)&arg2, sizeof(uint8_t), fp);
      LL = add2back(arg2, LL);
    }

    // Add to front
    else if (opcode == 1) {
      readByte((uint8_t *)&arg2, sizeof(uint8_t), fp);
      LL = add2front(arg2, LL);
    }

    // Insert node
    else if (opcode == 2) {
      readByte((uint16_t *)&arg1, sizeof(uint16_t), fp);
      readByte((uint8_t *) &arg2, sizeof(uint8_t), fp);
      LL = insertNode(arg2, arg1, LL);
    }

    // Remove last node
    else if (opcode == 3)
      LL = removeLastNode(LL);

    // Remove first node
    else if (opcode == 4)
      LL = removeFirstNode(LL);

    // Remove node from index
    else if (opcode == 5) {
      readByte((uint16_t *)&arg1, sizeof(uint16_t), fp);
      LL = popNode(arg1, LL);
    }

    printf("arg 1: %x (hex)\n", arg1);
    printf("arg 2: %x (hex)\n", arg2);

    printLL(LL);
  }
  printLL(LL);

  // Clean & exit
  fclose(fp);
  return EXIT_SUCCESS;
}
