#include "code.h"
#include "io.h"
#include "trie.h"
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
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
  TrieNode *root = trie_create();
  TrieNode *curr_node = root;
  TrieNode *prev_node = NULL;
  uint8_t curr_sym = 0;
  uint8_t prev_sym = 0;
  uint16_t next_code = START_CODE;

  while (read_sym(infile, &curr_sym)) {
    TrieNode *next_node = trie_step(curr_node, curr_sym);
    if (next_node != NULL) {
      prev_node = curr_node;
      curr_node = next_node;
       //printf("%c\n",curr_sym);
    } else {
      buffer_pair(outfile, curr_node->code, curr_sym, log2(next_code) + 1);
      curr_node->children[curr_sym] = trie_node_create(next_code);
      // printf("%c %d\n",curr_sym,curr_node->children[curr_sym]->code);
      curr_node = root;
      next_code += 1;
    }

    prev_sym = curr_sym;
  }

  // buffer_pair(outfile,3,&curr_sym,16);

  close(infile);
}
