// safe dial 0 - 99
// dial wraps around
// rotation = L or R
// dial starts at 50

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t u8;
typedef uint16_t u16;

typedef int8_t i8;
typedef int16_t i16;

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

  // (NOTE) Maybe I shouldn't store the new lines? It probably doesn't matter
  // I probably want to replace this with reading line by line anyways instead
  // of loading the entire file into memory
  fread(buffer, sizeof(char), file_size, file);
  // (NOTE) closing here might be pointless
  fclose(file);

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

    // printf("%i\n", parsed_int.parsed_value);
    dial_position += parsed_int.parsed_value;
    // printf("%i\n", dial_position);

    dial_position %= 100;

    if (dial_position == 0) {
      zero_count++;
    }

    printf("%c%i: %i\n", turn_direction, abs(parsed_int.parsed_value),
           dial_position);
  }

  printf("%i\n", zero_count);
  // printf("test: %i\n", string_to_int(&buffer[1]).parsed_value);

  return 0;
}
