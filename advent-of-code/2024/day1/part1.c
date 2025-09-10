// Title:       part1.c
// Description: Day1 AoC part1
// Author:      bluecosmo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

int compare(const void *left_ptr, const void *right_ptr) {
  int left = *(int*) left_ptr;
  int right = *(int*) right_ptr;
  return left - right;
}

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

  qsort(left_list, MAX_SIZE, sizeof(int), compare);
  qsort(right_list, MAX_SIZE, sizeof(int), compare);

  int sum = 0;
  for (int i = 0; i < MAX_SIZE; i++)
    sum += abs(left_list[i] - right_list[i]);

  printf("%d\n", sum);
  return EXIT_SUCCESS;
}
