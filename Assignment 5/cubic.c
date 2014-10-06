#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  float x, y;
} point;

void usage() {
  fprintf(stderr, "usage: cubic.o <outfile> <debug?> <steps> <cut line (t)> <p0.x> <p0.y> <p1.x> <p1.y> <p2.x> <p2.y> <p3.x> <p3.y>\n");
  exit(1);
}

int main(int argc, char *argv[]) {
  point p0, p1, p2, p3, q0, q1, q2, r0, s0, s1, c0, c1, c2, c3, c4;
  int color, debug, steps;
  float angle, cut, t;
  FILE * outFile;
  char buffer[1024];

  /* Check argument length */
  if (argc != 13) {
    usage();
  }

  /* Open output file */
  outFile = fopen(argv[1], "w");
  if (outFile == NULL) {
    fprintf(stderr, "Error, unable to open output file\n");
    exit(1);
  }

  color = 624;
  debug = atoi(argv[2]);
  steps = atoi(argv[3]);
  cut = atof(argv[4]);
  p0.x = atoi(argv[5]);
  p0.y = atoi(argv[6]);
  p1.x = atoi(argv[7]);
  p1.y = atoi(argv[8]);
  p2.x = atoi(argv[9]);
  p2.y = atoi(argv[10]);
  p3.x = atoi(argv[11]);
  p3.y = atoi(argv[12]);

  fputs("<svg xmlns='http://www.w3.org/2000/svg' width='300' height='300'>", outFile);
  fputs("<rect x='0' y='0' width='300' height='300' fill='none' stroke='black' stroke-width='15'/>", outFile);
  if (debug == 0 ) {
    sprintf(buffer, "<path d='M%.2f,%.2f C%.25f,%.2f %.2f,%.2f, %.2f, %.2f' fill='none' stroke='black' stroke-width='4'/>", p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
    fputs(buffer, outFile);
  }


  for (t = 0.0; t < 1.00001; t = t + 1.0/steps) {
    if (t >= 0.5) {
      color = 264;
    }
    q0.x = (1-t)*p0.x + t*p1.x;
    q0.y = (1-t)*p0.y + t*p1.y;

    q1.x = (1-t)*p1.x + t*p2.x;
    q1.y = (1-t)*p1.y + t*p2.y;

    q2.x = (1-t)*p2.x + t*p3.x;
    q2.y = (1-t)*p2.y + t*p3.y;

    s0.x = (1-t)*q0.x + t*q1.x;
    s0.y = (1-t)*q0.y + t*q1.y;

    s1.x = (1-t)*q1.x + t*q2.x;
    s1.y = (1-t)*q1.y + t*q2.y;

    r0.x = pow((1-t),2)*q0.x + 2*t*(1-t)*q1.x + pow(t,2)*q2.x;
    r0.y = pow((1-t),2)*q0.y + 2*t*(1-t)*q1.y + pow(t,2)*q2.y;

    angle = 180 - (atan2(s1.x-s0.x, s1.y-s0.y) * (180 / 3.14159265));

    if (t == cut) {
      c0.x = q0.x;
      c0.y = q0.y;
      c1.x = s0.x;
      c1.y = s0.y;
      c2.x = r0.x;
      c2.y = r0.y;
      c3.x = s1.x;
      c3.y = s1.y;
      c4.x = q2.x;
      c4.y = q2.y;
  }

    if (debug == 1) {
      sprintf(buffer, "<line x1='%.2f' y1='%2.f' x2='%.2f' y2='%.2f' stroke='#%d' stroke-width='1.5' />\n", q0.x, q0.y, q1.x, q1.y, color);
      fputs(buffer, outFile);

      sprintf(buffer, "<line x1='%.2f' y1='%2.f' x2='%.2f' y2='%.2f' stroke='#%d' stroke-width='1.5' />\n", q1.x, q1.y, q2.x, q2.y, color);
      fputs(buffer, outFile);

      sprintf(buffer, "<line x1='%.2f' y1='%2.f' x2='%.2f' y2='%.2f' stroke='lime' stroke-width='4' />\n", s0.x, s0.y, s1.x, s1.y);
      fputs(buffer, outFile);
    }

    sprintf(buffer, "<rect x='%.2f' y='%2.f' width='8' height='8' fill='orange' transform='rotate(%.2f %.2f %.2f)'/>\n", r0.x-4, r0.y-4, angle, r0.x, r0.y);
    fputs(buffer, outFile);

    printf("t: %.2f --- q0 = (%.2f, %.2f), q1 = (%.2f, %.2f), q2 = (%.2f, %.2f), s0 = (%.2f, %.2f), s1 = (%.2f, %.2f), r0 = (%.2f, %.2f), angle = %.2f\n", t, q0.x, q0.y, q1.x, q1.y, q2.x, q2.y, s0.x, s0.y, s1.x, s1.y, r0.x, r0.y, angle);
  }

  if (debug == 1) {
    sprintf(buffer, "<path d='M%.2f,%.2f C%.25f,%.2f %.2f,%.2f, %.2f, %.2f' fill='none' stroke='black' stroke-width='4'/>", p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
    fputs(buffer, outFile);
  }

  sprintf(buffer, "<path d='M%.2f, %.2f C%.2f, %.2f, %.2f, %.2f, %.2f, %.2f' fill='none' stroke='#c77' stroke-width='2'/>", p0.x, p0.y, c0.x, c0.y, c1.x, c1.y, c2.x, c2.y);
  fputs(buffer, outFile);
  sprintf(buffer, "<path d='M%.2f, %.2f C%.2f, %.2f, %.2f, %.2f, %.2f, %.2f' fill='none' stroke='#7c7' stroke-width='2'/>", c2.x, c2.y, c3.x, c3.y, c4.x, c4.y, p3.x, p3.y);
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
