// Title:       main.c
// Description: Day 16
// Author:      bluecosmo

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {

  FILE *fp = fopen("./input.txt", "r");
  if (!fp) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  fseek(fp, 0, SEEK_END);
  const size_t FILE_SIZE = ftell(fp);
  rewind(fp);

  /*size_t count = file_size / sizeof(TreeNode);*/
  /*TreeNode *tree = (TreeNode*) malloc(count * sizeof(TreeNode));*/
  /**/
  /*fread(tree, sizeof(TreeNode), count, fp);*/
  /**/
  /*getline(fp);*/


  return EXIT_SUCCESS;
}

