// Title:       part1.c
// Description: Day2 AoC part1
// Author:      bluecosmo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int iterate_nums(char *line_read) {

  char *num_from_file = strtok(line_read, " ");

  int prev_num = 0;
  int curr_num = 0;
  int valid_reports = 0;
  int direction = 0;
  int i = 0;

  for (i = 0; num_from_file; i++) {

    curr_num = atoi(num_from_file);

    printf("[%d]: c:%d p:%d\n", i, curr_num, prev_num);

    if (i > 0) {

      int diff = curr_num - prev_num;

      if (diff < -2 || diff > 2) { valid_reports = 0; break; }

      if (diff != 0) {

        if (direction == 0) {
          if (diff > 0) direction = 1;
          else direction = -1;
        }

        if ((direction > 0 && diff > 0) ||
            (direction < 0 && diff < 0))
          valid_reports++;
      }
    }
    prev_num = curr_num;
    num_from_file = strtok(NULL, " ");
  }
  return valid_reports;
}

int main(void) {

  FILE *fp = fopen("./input", "r");
  if (!fp) {
    perror("./input");
    return EXIT_FAILURE;
  }

  char *line_read = NULL;
  size_t line_length = 0;
  int reports = 0;

  while (getline(&line_read, &line_length, fp) != EOF) {
    reports += iterate_nums(line_read);
  }

  printf("%d\n", reports);
  return EXIT_SUCCESS;
}

