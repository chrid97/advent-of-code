#import "../util.c"
#include <stdio.h>

int main(void) {
  char *file = file_read("./day2.txt");
  for (int i = 0; i < 20; i++) {

    printf("%c", file[i]);
  }
}
