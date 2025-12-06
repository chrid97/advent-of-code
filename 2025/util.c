#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

char *file_read(char *path) {
  int fd = open(path, O_RDONLY);
  const size_t BUF_SIZE = 4096;
  char *buffer = malloc(BUF_SIZE);

  int read_result = pread(fd, buffer, BUF_SIZE, 0);
  if (read_result == -1) {
    printf("broken");
  }

  return buffer;
}
