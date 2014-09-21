#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void usage() {
  fprintf(stderr, "usage: robot <outfile> <angle1> <length1> <angle2> <length2> ...\n");
  exit(1);
}

double deg2rad(double degrees) {
  return degrees*(M_PI/180.0);
}

int main(int argc, char *argv[]) {
  /* Declare variables */
  FILE * outFile;
  int i;
  int SECTIONS;
  double curAngle;
  char buffer[1024];

  /* Check argument length */
  if (argc % 2 != 0) {
    usage();
  }

  /* Find number of sections needed and create arrays based on this */
  SECTIONS = (argc - 2) / 2;
  double angle[SECTIONS];
  double length[SECTIONS];
  double x[SECTIONS];
  double y[SECTIONS];

  /* Open output file */
  outFile = fopen(argv[1], "w");
  if (outFile == NULL) {
    fprintf(stderr, "Error, unable to open output file\n");
    exit(1);
  }

  /* Get angles from arguments */
  curAngle = 0;
  for (i = 0; i < SECTIONS; i++) {
    angle[i] = atoi(argv[i*2 + 2]);
    length[i] = atoi(argv[i*2 + 3]);

    /* Find initial end point */
    if (i == 0) {
      x[i] = length[i] * cos(deg2rad(angle[i]));
      y[i] = length[i] * sin(deg2rad(angle[i]));
      curAngle = angle[i];
    } else { // Find all endpoints after the first
      x[i] = x[i-1] + length[i] * cos(deg2rad(angle[i] + curAngle));
      y[i] = y[i-1] + length[i] * sin(deg2rad(angle[i] + curAngle));
      curAngle = curAngle + angle[i];
    }


    printf("Angle[%i]: %.2f°, Length[%i]: %.2f, Coords[%i]: (%.2f, %.2f)\n", i, angle[i], i, length[i], i, x[i], y[i]);
  }



  /* Set up definitions */
  fputs("<!-- Uses some of the sample code for the robot arm, as provided on the course site -->\n", outFile);
  fputs("<!-- CS559 Assignment 3 Example - robot arm - by Michael Gleicher -->\n", outFile);
  fputs("<!-- you may use this example as a starting point for your own work, but course policy requires proper attribution -->\n", outFile);
  fputs("<svg xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink' height='250px' width='400px' viewBox='-50 -50 100 75'>\n", outFile);
  fputs("<defs>\n", outFile);
  fputs("  <circle id='dot' cx='0' cy='0' r='1' stroke='black' stroke-width='.5' fill='rgb(255,98,0)'/>\n", outFile);
  fputs("  <rect id='endbox' x='-3' y='-3' height='6' width='6' fill='blue' opacity='.5' stroke='rgb(70,111,213)'/>\n", outFile);
  fputs("</defs>\n", outFile);

  /* Set up grid */
  for (i = -10; i < 11; i++) {
    sprintf(buffer, "<line x1='-50' y1='%i' x2='50' y2='%i' stroke='#aaa' stroke-width='.5' />\n", i*5, i*5);
    fputs(buffer, outFile);
    sprintf(buffer, "<line x1='%i' y1='-50' x2='%i' y2='25' stroke='#aaa' stroke-width='.5' />\n", i*5, i*5);
    fputs(buffer, outFile);
  }

  fputs("<line x1='0' y1='-50' x2='0' y2='25' stroke='#333' stroke-width='.5' />\n", outFile);
  fputs("<line x1='-50' y1='0' x2='50' y2='0' stroke='#333' stroke-width='.5' />\n", outFile);
  fputs("<rect x='-50' y='-50' height='75' width='100' stroke='black' fill='none' />\n", outFile);


  /* Actual svg */
  for (i = 0; i < SECTIONS; i++) {
    if (i == 0) {
      sprintf(buffer, "<g transform='scale(1,-1)rotate(%f)'>\n", angle[i]);
      fputs(buffer, outFile);
    } else {
      sprintf(buffer, "<g transform='translate(%f,0)rotate(%f)'>\n", length[i-1], angle[i]);
      fputs(buffer, outFile);
    }

    sprintf(buffer, "<rect id='segment' x='0' y='-2' height='4' width='%f' stroke='rgb(103,227,0)' fill='rgb(18,62,171)'/>\n", length[i]);
    fputs(buffer, outFile);
    fputs("<use xlink:href='#dot' />\n", outFile);
  }

  /* Complete rest of last shape */
  sprintf(buffer, "<g transform='translate(%f,0)'>\n", length[SECTIONS-1]);
  fputs(buffer, outFile);
  fputs("<use xlink:href='#endbox' />\n", outFile);
  fputs("<use xlink:href='#dot' />\n", outFile);

  /* Close all groups */
  for (i=0; i < SECTIONS + 1; i++) {
    fputs("</g>\n", outFile);
  }

  /* EOF */
  fputs("</svg>", outFile);

  exit(0);

}
