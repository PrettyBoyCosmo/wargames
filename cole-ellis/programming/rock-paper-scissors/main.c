// Title:       main.c
// Description: Rock Paper Scissors Solution (Cole Ellis)
// Author:      bluecosmo

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getScore(char enemy_move, char player_move) {
  int part1 = 0;

  if (player_move == 'X') part1 = 1;
  if (player_move == 'Y') part1 = 2;
  if (player_move == 'Z') part1 = 3;

  if ((player_move == 'X' && enemy_move == 'C') ||
      (player_move == 'Y' && enemy_move == 'A') ||
      (player_move == 'Z' && enemy_move == 'B'))
    part1 += 6;

  if ((player_move == 'X' && enemy_move == 'A') ||
      (player_move == 'Y' && enemy_move == 'B') ||
      (player_move == 'Z' && enemy_move == 'C'))
    part1 += 3;

  return part1;
}

int determineMove(char enemy_move, char outcome) {
  char player_move;

  if (outcome == 'X') {
    if (enemy_move == 'A') player_move = 'Z';
    if (enemy_move == 'B') player_move = 'X';
    if (enemy_move == 'C') player_move = 'Y';
  }

  if (outcome == 'Y') {
    if (enemy_move == 'A') player_move = 'X';
    if (enemy_move == 'B') player_move = 'Y';
    if (enemy_move == 'C') player_move = 'Z';
  }

  if (outcome == 'Z') {
    if (enemy_move == 'A') player_move = 'Y';
    if (enemy_move == 'B') player_move = 'Z';
    if (enemy_move == 'C') player_move = 'X';
  }

  return getScore(enemy_move, player_move);
}

int main(void) {

  FILE *fp = fopen("./input.txt", "r");
  if (!fp) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  char *line_read = NULL;
  size_t line_length = 0;
  int part1 = 0;
  int part2 = 0;

  while (getline(&line_read, &line_length, fp) != -1) {
    char enemy_move = line_read[0];
    char player_move = line_read[2];

    printf("Enemy: %c\n", enemy_move);
    printf("Player: %c\n", player_move);

    part1 += getScore(enemy_move, player_move);
    part2 += determineMove(enemy_move, player_move);

    printf("[+] Part1: %d\n", part1);
    printf("[+] Part2: %d\n", part2);
  }

  printf("Cosmo:\t flag{%d_%d}\n", part1, part2);
  printf("Ellis:\t flag{6675_7831}\n");
  return EXIT_SUCCESS;
}

