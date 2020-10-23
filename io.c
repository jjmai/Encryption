#include "io.h"
#include "code.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#define BLOCK 4096
static uint8_t buffer[BLOCK];
static uint8_t word[BLOCK];
static int lines = 0, line_count = 0, bit_index;

// read each character and return
bool read_sym(int infile, uint8_t *sym) {
  if (line_count == 0) {
    lines = read(infile, buffer, BLOCK);
    if (lines == 0)
      return false;
  }
  *sym = buffer[line_count];
  line_count = (line_count + 1) % lines;

  return true;
}

void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen) {
  uint16_t temp = 0;
  // code into bit
  for (int i = 0; i < bitlen; i++) {
    if (code & (1 << i)) {
      word[bit_index / 8] |= 1 << (bit_index % 8);
      // printf("1");
    } else {
      word[bit_index / 8] &= ~(1 << (bit_index % 8));
      // printf("0");
    }
    bit_index++;
  }
  printf("%d !",sym);
  for (int i = 0; i < log2(sym)+1; i++) {
    if (sym & (1 << i)) {
      //word[bit_index / 8] |= 1 << (bit_index % 8);
      printf("1\n");
    } else {
      word[bit_index / 8] &= ~(1 << (bit_index % 8));
      //printf("0\n");
    }
    bit_index++;
  }
  
}

