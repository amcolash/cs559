#include <stdio.h>
#include <stdlib.h>

#define SECTIONS 4

void usage() {
  fprintf(stderr, "usage: robot <outfile> <length1> <angle1> <length2> <angle2> <length3> <angle3> <length4> <angle4>\n");
  exit(1);
}

int main(int argc, char *argv[]) {

  /* Declare variables */
  FILE * outFile;
  int angle[SECTIONS];
  int length[SECTIONS];
  int i;
  char buffer[1024];

  /* Check argument length */
  if (argc != 10) {
    usage();
  }

  /* Open output file */
  outFile = fopen(argv[1], "w");
  if (outFile == NULL) {
    fprintf(stderr, "Error, unable to open output file\n");
    exit(1);
  }

  /* Get angles from arguments */
  for (i = 0; i < SECTIONS; i++) {
    angle[i] = atoi(argv[i*2 + 2]);
    length[i] = atoi(argv[i*2 + 3]);
  }

  printf("Angles: %i, %i, %i, %i\n", angle[0], angle[1], angle[2], angle[3]);
  printf("Lengths: %i, %i, %i, %i\n", length[0], length[1], length[2], length[3]);


  /* Set up definitions */
  fputs("<!-- Uses some of the sample code for the robot arm, as provided on the course site -->\n", outFile);
  fputs("<!-- CS559 Assignment 3 Example - robot arm - by Michael Gleicher -->\n", outFile);
  fputs("<!-- you may use this example as a starting point for your own work, but course policy requires proper attribution -->\n", outFile);
  fputs("<svg xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink' height='250px' width='400px' viewBox='-50 -50 100 75'>\n", outFile);
  fputs("<defs>\n", outFile);
  fputs("  <circle id='dot' cx='0' cy='0' r='1' stroke='black' stroke-width='.5' fill='gold'/>\n", outFile);
  fputs("  <rect id='endbox' x='-3' y='-3' height='6' width='6' fill='blue' opacity='.5' stroke='blue'/>\n", outFile);
  fputs("</defs>\n", outFile);

  /* Set up grid */
  fputs("<rect x='-50' y='-50' height='75' width='100' stroke='black' fill='#EEE' />\n", outFile);
  fputs("<line x1='0' y1='-50' x2='0' y2='25' stroke='#888' stroke-width='.5' />\n", outFile);
  fputs("<line x1='-50' y1='0' x2='50' y2='0' stroke='#888' stroke-width='.5' />\n", outFile);

  /* Actual svg */
  for (i = 0; i < SECTIONS; i++) {
    if (i == 0) {
      sprintf(buffer, "<g transform='scale(1,-1)rotate(%i)'>\n", angle[i]);
      fputs(buffer, outFile);
    } else {
      sprintf(buffer, "<g transform='translate(%i,0)rotate(%i)'>\n", length[i-1], angle[i]);
      fputs(buffer, outFile);
    }

    sprintf(buffer, "<rect id='segment' x='0' y='-2' height='4' width='%i' stroke='lime' fill='rgb(50,50,90)'/>\n", length[i]);
    fputs(buffer, outFile);
    fputs("<use xlink:href='#dot' />\n", outFile);
  }

  printf("length[i-1]: %i, length[i]: %i\n", length[i-1], length[i]);

  sprintf(buffer, "<g transform='translate(%i,0)'>\n", length[SECTIONS-1]);
  fputs(buffer, outFile);
  fputs("<use xlink:href='#endbox' />\n", outFile);
  fputs("<use xlink:href='#dot' />\n", outFile);

  for (i=0; i < SECTIONS + 1; i++) {
    fputs("</g>\n", outFile);
  }

  fputs("</svg>", outFile);

  exit(0);

}

void rotateAtCenter() {

}
