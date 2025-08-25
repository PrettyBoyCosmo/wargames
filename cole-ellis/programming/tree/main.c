// Title:       main.c
// Description: Tree solution (Cole Ellis)
// Author:      bluecosmo

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct __attribute__((__packed__)) TreeNode {
  uint16_t index;
  uint8_t value;
  uint16_t left;
  uint16_t right;
} TreeNode;

void printTreeNode(TreeNode *node) {
  printf("Index: 0x%04x\n", node->index);
  printf("Value: 0x%04x\n", node->value);
  printf("Left: 0x%04x\n", node->left);
  printf("Right: 0x%04x\n\n", node->right);
}

int compare(const void *left_ptr, const void *right_ptr) {
  const TreeNode* left = (TreeNode*) left_ptr;
  const TreeNode* right = (TreeNode*) right_ptr;
  return (int) (left->index - right->index);
}

void preOrder(uint16_t index, TreeNode *root) {
  printf("%c", root[index - 1].value);

  if (root[index - 1].left == 0xFFFF && root[index - 1].right == 0xFFFF) return;

  if (root[index - 1].left != 0xFFFF)
    preOrder(root[index - 1].left, root);
  if (root[index - 1].right != 0xFFFF)
    preOrder(root[index - 1].right, root);
}

int main(void) {

  FILE *fp = fopen("./data.bin", "rb");
  if (!fp) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  fseek(fp, 0, SEEK_END);
  size_t file_size = ftell(fp);
  rewind(fp);
  size_t count = file_size / sizeof(TreeNode);

  TreeNode *root = (TreeNode*) malloc(count * sizeof(TreeNode));
  for (uint16_t i = 0; fread(&root[i], sizeof(TreeNode), 1, fp); i++) {
    printTreeNode(&root[i]);
  }

  printf("[*] Sorting...\n");
  qsort(root, count, sizeof(TreeNode), compare);
  for (uint16_t i = 0; i < count; i++) {
    printTreeNode(&root[i]);
  }

  preOrder(1, root);

  return EXIT_SUCCESS;
}
