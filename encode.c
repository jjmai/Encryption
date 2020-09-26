#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "trie.h"
#include "io.h"
#include <fcntl.h> 
#include<sys/types.h>
#include<sys/stat.h> 
int main(int argc, char *argv[]) {
  int infile = STDIN_FILENO;
  int outfile = STDOUT_FILENO;
  int opt;
  while ((opt = getopt(argc, argv, "vi:o:")) != EOF) {
    switch (opt) {
    case 'v':
      break;
    case 'i':
      infile = open(optarg, O_RDONLY | O_CREAT);
      break;
    case 'o':
      outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
       break;
    default:
      printf("?");
      exit(1);
    }
  }
  // read in
  uint8_t curr_sym=0;
 
  TrieNode *root = trie_create();
  
  close(infile);
}
