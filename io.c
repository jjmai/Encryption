#include "io.h"
#include "code.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#define BLOCK 4096
static uint8_t buffer[BLOCK];
static int lines=0,line_count=0;

//read each character and return
bool read_sym(int infile, uint8_t *sym) {
  if(line_count==0) {
    lines = read(infile,buffer, BLOCK);
    if(lines==0) return false;
   }
   *sym = buffer[line_count];
   printf("%c\n",*sym);
   line_count=(line_count+1)%lines;
  
  return true; 
}
