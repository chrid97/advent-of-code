#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
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

typedef struct {
  char *buffer;
  int size;
} ReadFileResult;
ReadFileResult file_read(char *path) {
  int fd = open(path, O_RDONLY);
  struct stat fd_stat = {0};
  int fstat_result = fstat(fd, &fd_stat);
  const size_t BUF_SIZE = fd_stat.st_size;
  char *buffer = malloc(BUF_SIZE);
  int read_result = pread(fd, buffer, BUF_SIZE, 0);
  if (read_result == -1) {
    printf("broken\n");
  }

  return (ReadFileResult){.buffer = buffer, .size = fd_stat.st_size};
}
