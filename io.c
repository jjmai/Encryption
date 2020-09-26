#include "io.h"
#include "code.h"
#include <stdlib.h>
#include <stdio.h>
#define BLOCK 4096
static uint8_t buffer[BLOCK];
bool read_sym(int infile, uint8_t *sym) {
  fscanf(infile,"%s",buffer); 
  printf("%c",buffer[0]); 
  return true; 
}
