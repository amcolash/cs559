#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  float x, y;
} point;

void usage() {
  fprintf(stderr, "usage: cubic.o <outfile> <p0.x> <p0.y> <p1.x> <p1.y> <p2.x> <p2.y> <p3.x> <p3.y>\n");
  exit(1);
}

int main(int argc, char *argv[]) {
  point p0, p1, p2, p3, q0, q1, q2, r0;
  int color, steps;
  float angle, t;
  FILE * outFile;
  char buffer[1024];

  /* Check argument length */
  if (argc != 11) {
    usage();
  }

  /* Open output file */
  outFile = fopen(argv[1], "w");
  if (outFile == NULL) {
    fprintf(stderr, "Error, unable to open output file\n");
    exit(1);
  }

  fputs("<svg xmlns='http://www.w3.org/2000/svg' width='300' height='300'>", outFile);
  fputs("<rect x='0' y='0' width='300' height='300' fill='none' stroke='black' stroke-width='15'/>", outFile);


  color = 735;

  steps = atoi(argv[2]);
  p0.x = atoi(argv[3]);
  p0.y = atoi(argv[4]);
  p1.x = atoi(argv[5]);
  p1.y = atoi(argv[6]);
  p2.x = atoi(argv[7]);
  p2.y = atoi(argv[8]);
  p3.x = atoi(argv[9]);
  p3.y = atoi(argv[10]);

  for (t = 0.0; t < 1.00001; t = t + 1.0/steps) {
    if (t >= 0.5) {
      color = 375;
    }
    q0.x = (1-t)*p0.x + t*p1.x;
    q0.y = (1-t)*p0.y + t*p1.y;

    q1.x = (1-t)*p1.x + t*p2.x;
    q1.y = (1-t)*p1.y + t*p2.y;

    q2.x = (1-t)*p2.x + t*p3.x;
    q2.y = (1-t)*p2.y + t*p3.y;

    r0.x = (1-t)*q0.x + t*q1.x;
    r0.y = (1-t)*q0.y + t*q1.y;

    angle = 180 - (atan2(q1.x-q0.x, q1.y-q0.y) * (180 / 3.14159265));

    sprintf(buffer, "<line x1='%.2f' y1='%2.f' x2='%.2f' y2='%.2f' stroke='#%d' stroke-width='1.5' />\n", q0.x, q0.y, q1.x, q1.y, color);
    fputs(buffer, outFile);

    sprintf(buffer, "<line x1='%.2f' y1='%2.f' x2='%.2f' y2='%.2f' stroke='#%d' stroke-width='1.5' />\n", q1.x, q1.y, q2.x, q2.y, color);
    fputs(buffer, outFile);

    sprintf(buffer, "<rect x='%.2f' y='%2.f' width='8' height='8' fill='orange' transform='rotate(%.2f %.2f %.2f)'/>\n", r0.x-4, r0.y-4, angle, r0.x, r0.y);
    //fputs(buffer, outFile);

    printf("t: %.2f --- q0 = (%.2f, %.2f), q1 = (%.2f, %.2f), r0 = (%.2f, %.2f), angle = %.2f\n", t, q0.x, q0.y, q1.x, q1.y, r0.x, r0.y, angle);
  }

  sprintf(buffer, "<path d='M%.2f,%.2f C%.25f,%.2f %.2f,%.2f, %.2f, %.2f' fill='none' stroke='black' stroke-width='2'/>", p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
  fputs(buffer, outFile);

  sprintf(buffer, "<circle cx='%.2f' cy='%.2f' r='8' fill='blue'/>", p0.x, p0.y);
  fputs(buffer, outFile);
  sprintf(buffer, "<circle cx='%.2f' cy='%.2f' r='8' fill='blue'/>", p3.x, p3.y);
  fputs(buffer, outFile);
  sprintf(buffer, "<circle cx='%.2f' cy='%.2f' r='8' fill='red'/>", p1.x, p1.y);
  fputs(buffer, outFile);
  sprintf(buffer, "<circle cx='%.2f' cy='%.2f' r='8' fill='red'/>", p2.x, p2.y);
  fputs(buffer, outFile);

  fputs("</svg>", outFile);

  return 0;
}
