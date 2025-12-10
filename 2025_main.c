#include <assert.h>
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

typedef struct IntParseResult {
  u8 digit_count;
  int parsed_value;
} IntParseResult;
IntParseResult string_to_int(char *str) {
  int i = 0;
  int result = 0;
  while (str[i] != '\0') {
    if (str[i] >= '0' && str[i] <= '9') {
      result = (result * 10) + str[i] - 48;
    } else {
      break;
    }
    i++;
  }

  return (IntParseResult){.digit_count = i, .parsed_value = result};
}

void day1(char *buffer, int file_size) {
  int dial_position = 50;
  int zero_count = 0;

  printf("The dial starts by pointing at %i\n", dial_position);
  int i = 0;
  while (i < file_size) {
    char turn_direction = buffer[i];
    IntParseResult parsed_int = string_to_int(&buffer[i + 1]);
    // value shouldn't be zero?
    assert(parsed_int.parsed_value);
    i += parsed_int.digit_count + 2;

    if (turn_direction == 'L') {
      parsed_int.parsed_value = -parsed_int.parsed_value;
    }

    dial_position += parsed_int.parsed_value;
    dial_position %= 100;

    if (dial_position == 0) {
      zero_count++;
    }

    printf("%c%i: %i\n", turn_direction, abs(parsed_int.parsed_value),
           dial_position);
  }

  printf("%i\n", zero_count);
}

int main(void) {
  ReadFileResult file = file_read("data/day1.txt");
  day1(file.buffer, file.size);

  return 0;
}
