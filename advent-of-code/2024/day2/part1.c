// Title:       part1.c
// Description: Day 2 AoC Part 1
// Author:      bluecosmo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool checkReport(int *nums) {
}

int main(void) {

  FILE *fp = fopen("./input", "r");
  if (!fp) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  char *line_read = NULL;
  size_t line_length = 0;

  int safe_reports = 0;

  while (getline(&line_read, &line_length, fp) != EOF) {

    char *num_read = strtok(line_read, " ");
    int curr_num = 0;
    int prev_num = curr_num;
    int direction = 0;

    for (int i = 0; num_read; i++) {

      printf("PREV: %d\n", prev_num);
      printf("CURR: %d\n", curr_num);

      curr_num = atoi(num_read);

      if (i > 0) {

        int difference = prev_num - curr_num;

        if (direction == 0) {
          if (prev_num > curr_num) direction = -1;
          else direction = +1;
        }

        if (direction == 1 && (0 < difference && 2 >= difference)) {
          safe_reports++;
        }

        else if (direction == -1 && (0 > difference && -2 <= difference)) {
          safe_reports++;
        }

        prev_num = curr_num;
        num_read = strtok(NULL, " ");
      }
    }
  }

  printf("%d\n", safe_reports);
  return EXIT_SUCCESS;
}

