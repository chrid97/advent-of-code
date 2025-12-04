// safe dial 0 - 99
// dial wraps around
// rotation = L or R
// dial starts at 50

#include <stdio.h>
#include <stdlib.h>
int main(void) {
  FILE *file = fopen("day1.txt", "r");
  if (file == NULL) {
    fprintf(stderr, "Failed to open file.\n");
    return 1;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);
  char *buffer = malloc(file_size + 1);
  if (!buffer) {
    fprintf(stderr, "Failed to allocate buffer.\n");
    return 1;
  }

  fread(buffer, sizeof(char), file_size, file);
  printf("%s", buffer);
  // closing here might be pointless
  fclose(file);

  int dial_ptr = 0;
  int zero_count = 0;

  return 0;
}
