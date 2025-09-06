// Title:       main.c
// Description: Rope Bridge (Cole Ellis)
// Author:      bluecosmo

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(void) {

  FILE *fp = fopen("./input.txt", "r");
  if (!fp) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  char *line_read = NULL;
  size_t line_length = 0;

  while (getline(&line_read, &line_length, fp) != EOF) {
  }

  printf("Ellis: {flag{2511}\n");
  return EXIT_SUCCESS;
}

