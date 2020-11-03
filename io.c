#include "io.h"
#include "code.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define BLOCK 4096
static uint8_t buffer[BLOCK] = {0};
static uint8_t word[BLOCK] = {0};
static int line_count = 0, bit_index;

void read_header(int infile, FileHeader *header) {
  struct stat protection;
  fstat(infile, &protection);
  header->protection = protection.st_mode;
  read(infile, header, sizeof(FileHeader));
  if (header->magic != 0x8badbeef) {
    printf("bad magic number");
    exit(1);
  }
  // dsize += sizeof(FileHeader);
}

void write_header(int outfile, FileHeader *header) {
  header->magic = MAGIC;
  struct stat protection;
  fstat(outfile, &protection);
  header->protection = protection.st_mode;
  write(outfile, header, sizeof(FileHeader));
  // csize += sizeof(FileHeader);
}

// read each character and return
bool read_sym(int infile, uint8_t *sym) {

  if (line_count == 0 || line_count > BLOCK) {
    int lines = read(infile, buffer, BLOCK);
    if (lines == 0)
      return false;
  }
  *sym = buffer[line_count];
  line_count = (line_count + 1) % BLOCK;

  return true;
}

void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen) {

  // uint16_t c = code;
  for (int i = 0; i < bitlen; i++) {
    if (bit_index == BLOCK * 8) {
      flush_pairs(outfile);
      bit_index = 0;
    }
    if (code & (1 << i)) {
      word[bit_index / 8] |= 1 << (bit_index % 8);
    } else {
      word[bit_index / 8] &= ~(1 << (bit_index % 8));
    }
    bit_index++;
  }
  // code in sym
  // uint8_t s = sym;
  for (int i = 0; i < 8; i++) {
    if (bit_index == BLOCK * 8) {
      flush_pairs(outfile);
      bit_index = 0;
    }
    if (sym & (1 << i)) {
      word[bit_index / 8] |= 1 << (bit_index % 8);
    } else {
      word[bit_index / 8] &= ~(1 << (bit_index % 8));
    }
    bit_index++;
  }
}

void flush_pairs(int outfile) { write(outfile, word, bit_index); }
