// Title:       main.c
// Description: Watch The Register (Cole Ellis)
// Author:      bluecosmo

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int main(void) {

  FILE *fp = fopen("./input.txt", "r");
  if (!fp) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  size_t cycle = 1;
  int8_t x = 1;
  char *line_read = NULL;
  size_t line_length = 0;
  char display[240] = {0};

  while (getline(&line_read, &line_length, fp) != -1) {

    printf("\nCycle:\t %ld\n", cycle);

    int32_t pixel = (cycle - 1) % 40;
    printf("Pixel:\t %d\n", pixel);
    printf("X:\t %d\n", x);
    printf("|x - pixel| = %d\n", abs(x - pixel));

    if (abs(x - pixel) <= 1)
      display[cycle - 1] = '#';
    else
     display[cycle - 1] = '.';

    cycle++;
    pixel = (cycle - 1) % 40;

    char *operation = strtok(line_read, " ");
    if (strcmp(operation, "noop\n") == 0) continue;

    printf("\nCycle:\t %ld\n", cycle);
    printf("Pixel:\t %d\n", pixel);
    printf("X:\t %d\n", x);

    if (abs(x - pixel) <= 1)
      display[cycle - 1] = '#';
    else
      display[cycle - 1] = '.';

    cycle++;
    x += atoi(strtok(NULL, " "));
  }

  printf("\n");
  for (size_t i = 0; i < 6; ++i) {
    for (size_t j = 0; j < 40; ++j) {
      printf("%c", display[40*i + j]);
    }
    printf("\n");
  }

  return EXIT_SUCCESS;
}

