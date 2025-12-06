#include "../util.c"
#include <stdio.h>

int main(void) {
  ReadFileResult file = file_read("./day2.txt");
  for (int i = 0; i < file.size; i++) {
    printf("%c", file.buffer[i]);
  }
}
