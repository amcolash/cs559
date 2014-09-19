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
  char buffer[1024];

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



  /* Set up definitions */
  fputs("<!-- Uses some of the sample code for the robot arm, as provided on the course site -->\n", outFile);
  fputs("<!-- CS559 Assignment 3 Example - robot arm - by Michael Gleicher -->\n", outFile);
  fputs("<!-- you may use this example as a starting point for your own work, but course policy requires proper attribution -->\n", outFile);
  fputs("<svg xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink' height='250px' width='400px' viewBox='-50 -50 100 75'>\n", outFile);
  fputs("<defs>\n", outFile);
  fputs("  <rect id='segment' x='0' y='-2' height='4' width='10' stroke='lime' fill='cyan'/>\n", outFile);
  fputs("  <circle id='dot' cx='0' cy='0' r='1' stroke='black' stroke-width='.5' fill='#CCC'/>\n", outFile);
  fputs("  <rect id='endbox' x='-3' y='-3' height='6' width='6' fill='blue' opacity='.5' stroke='blue'/>\n", outFile);
  fputs("</defs>\n", outFile);

  /* Set up grid */
  fputs("<rect x='-50' y='-50' height='75' width='100' stroke='black' fill='#EEE' />\n", outFile);
  fputs("<line x1='0' y1='-50' x2='0' y2='25' stroke='#888' stroke-width='.5' />\n", outFile);
  fputs("<line x1='-50' y1='0' x2='50' y2='0' stroke='#888' stroke-width='.5' />\n", outFile);

  /* Actual svg */
  for (i = 0; i < 4; i++) {
    if (i == 0) {
      sprintf(buffer, "<g transform='scale(1,-1)rotate(%i)'>\n", angle[i]);
      fputs(buffer, outFile);
    } else {
      sprintf(buffer, "<g transform='translate(10,0)rotate(%i)'>\n", angle[i]);
      fputs(buffer, outFile);
    }

    if (i < 3) {
      fputs("<use xlink:href='#segment' />\n", outFile);
    } else {
      fputs("<use xlink:href='#endbox' />\n", outFile);
    }
    fputs("<use xlink:href='#dot' />\n", outFile);
  }

  for (i=0; i < 4; i++) {
    fputs("</g>\n", outFile);
  }

  fputs("</svg>", outFile);

  // fputs("  <g transform='translate(10,0) rotate(-45)'>", outFile);
  // fputs("    <use xlink:href='#segment' />", outFile);
  // fputs("    <use xlink:href='#dot' />", outFile);
  // fputs("    <g transform='translate(10,0) rotate(45)'>", outFile);
  // fputs("      <use xlink:href='#segment' />", outFile);
  // fputs("      <use xlink:href='#dot' />", outFile);
  // fputs("      <g transform='translate(10,0) rotate(90)'>", outFile);
  // fputs("        <use xlink:href='#segment' />", outFile);
  // fputs("        <use xlink:href='#dot' />", outFile);
  // fputs("        <g transform='translate(10,0)'>", outFile);
  // fputs("          <use xlink:href='#dot' />", outFile);
  // fputs("          <use xlink:href='#redbox' />", outFile);
  // fputs("        </g>", outFile);
  // fputs("      </g>", outFile);
  // fputs("    </g>", outFile);
  // fputs("  </g>", outFile);
  // fputs("</g>", outFile);
  // fputs("</svg>", outFile);



  // for (i = 0; i < 4; i++) {
  //   if (i == 0) {
  //     printf("Got 0\n");
  //   } else {
  //   }
  //   sprintf(buffer, "<rect x='%i' y='%i' width='' height='%i' fill='rgb(%i, %i, %i)' transform='rotate(%i 150 150)'/>\n", angle[i], angle[i], angle[i], angle[i], angle[i], angle[i]);
  //   //fputs(buffer, outFile);
  // }

  exit(0);

}
