// Title:       main.c
// Description: TeLeVision solution (Cole Ellis)
// Author:      bluecosmo

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isPrime(uint8_t n) {
  if (n <= 1) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;

  for (int i = 3; i * i <= n; i += 2)
    if (n % i == 0) return false;

  return true;
}

int main(void) {

  FILE *fp = fopen("./data.bin", "rb");
  if (!fp) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  uint8_t tag;
  uint8_t length;
  uint32_t index = 0;
  uint8_t *flag = (uint8_t*) malloc(1200 * sizeof(uint8_t));

  while (fread(&tag, sizeof(uint8_t), 1, fp)) {

    fread(&length, sizeof(uint8_t), 1, fp);
    uint8_t *value = (uint8_t*) malloc(length * sizeof(uint8_t));
    fread(value, length, 1, fp);

    if (!isPrime(tag)) continue;

    printf("[+] tag:\t 0x%02x\n", tag);
    printf("[+] length:\t 0x%02x\n", length);
    printf("[+] value:\t %s\n\n", value);

    for (uint32_t i = 0; i < length; i++) {
      flag[index + i] = value[i];
    }
    index += length;
  }

  size_t flag_length = strlen((const char*)flag);
  printf("[+] values:\n%s\n\n", flag);

  // First 8
  printf("Cosmo:\t flag{%.*s", 8, flag);

  // Middle 8
  size_t middle_eight = flag_length / 2 - 4;
  printf("%.*s", 8, flag + middle_eight);

  // Final 8
  printf("%s}\n", &flag[flag_length - 8]);

  // Ellis's flag
  printf("Ellis:\t flag{&dGe04H<H&jNBSzT1h/7jf;h}\n");

  return EXIT_SUCCESS;
}

