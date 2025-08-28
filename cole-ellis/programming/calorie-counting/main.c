// Title:       main.c
// Description: Calorie Counting Solution (Cole Ellis)
// Author:      bluecosmo

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare(const void *x, const void *y) {
  return *(int*)y - *(int*)x;
}

int main(void) {

  FILE *fp = fopen("./input.txt", "r");
  if (!fp) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  char *line_read = NULL;
  size_t line_length = 0;
  int num_of_cals_total = 0, i = 0, cal_totals[240] = {0};

  while (getline(&line_read, &line_length, fp) != -1) {

    int num_of_cals_read = atoi(line_read);
    printf("[+] Number read: %d\n", num_of_cals_read);

    if (num_of_cals_read == 0) i++;

    cal_totals[i] += num_of_cals_read;

    printf("[+] cal_totals[%d] = %d\n", i, cal_totals[i]);
  }

  qsort(cal_totals, 240, sizeof(int), compare);

  printf("Cosmo:\t flag{%d}\n", (cal_totals[0] + cal_totals[1] + cal_totals[2]));
  printf("Ellis:\t flag{209914}\n");

  return EXIT_SUCCESS;
}
