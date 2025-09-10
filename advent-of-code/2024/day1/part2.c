// Title:       part2.c
// Description: Day1 AoC part2
// Author:      bluecosmo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

int main(void) {

  FILE *fp = fopen("./input", "r");
  if (!fp) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  int left_list[MAX_SIZE] = {0};
  int right_list[MAX_SIZE] = {0};

  char *line_read = NULL;
  size_t line_size = 0;

  for (int i = 0; getline(&line_read, &line_size, fp) != EOF; i++) {
    left_list[i] = atoi(strtok(line_read, " "));
    right_list[i] = atoi(strtok(NULL, " "));
  }

  int sum = 0;
  for (int i = 0; i < MAX_SIZE; i++)
    for (int j = 0; j < MAX_SIZE; j++)
      if (left_list[i] == right_list[j]) sum += left_list[i];

  printf("%d\n", sum);
  return EXIT_SUCCESS;
}
