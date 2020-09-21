#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  FILE *infile = stdin;
  FILE *outfile = stdout;
  int opt;
  while ((opt = getopt(argc, argv, "vi:o:")) != EOF) {
    switch (opt) {
    case 'v':
      break;
    case 'i':
      infile = fopen(optarg, "r");
    case 'o':
      outfile = fopen(optarg, "w");
    default:
      exit(1);
    }
  }
}
