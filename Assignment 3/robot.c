#include <stdio.h>
#include <stdlib.h>

void usage() {
  fprintf(stderr, "usage: robot <outfile> <angle1> <angle2> <angle3> <angle4>\n");
  exit(1);
}

int main(int argc, char *argv[]) {

  /* Declare variables */
  FILE * outFile;
  int angle[4];
  int i;
  char buffer[4096];

  /* Check argument length */
  if (argc != 6) {
    usage();
  }

  /* Open output file */
  outFile = fopen(argv[1], "w");
  if (outFile == NULL) {
    fprintf(stderr, "Error, unable to open output file\n");
    exit(1);
  }

  /* Get angles from arguments */
  for (i = 0; i < 4; i++) {
    angle[i] = atoi(argv[i+2]);
  }

  printf("Angles: %i, %i, %i, %i\n", angle[0], angle[1], angle[2], angle[3]);

  fputs("<svg xmlns='http://www.w3.org/2000/svg' height='300px' width='300px'>\n", outFile);


  fputs("<rect x='100' y='100' width='100' height='100' fill='red'/>\n", outFile);
  fputs("</svg>", outFile);

  exit(0);

}
