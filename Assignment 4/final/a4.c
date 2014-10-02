#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 300
#define HEIGHT 300

void usage() {
  fprintf(stderr, "usage: a4 <outfile> <ex> <ey> <ez> <gx> <gy> <gz> <tx> <ty> <tz> <frustum angle> <x1> <y1> <x2> <y2> ...\n");
  fprintf(stderr, "note: e - look from, c - look at, t - up vector");
  exit(1);
}

/*
int * divArray(int constant, int array[][4]) {
  int i, j;
  static int temp[4][4];
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      temp[i][j] = array[i][j] / constant;
    }
  }
  return temp;
}

int * multArray(int constant, int array[][4]) {
  int i, j;
  static int temp[4][4];
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      temp[i][j] = array[i][j] * constant;
    }
  }
  return temp;
}
*/

int * multVector(int constant, int array[3]) {
  static int temp[3];

  temp[0] = array[0] * constant;
  temp[1] = array[1] * constant;
  temp[2] = array[2] * constant;

  return temp;
}

int * divVector(int constant, int array[3]) {
  static int temp[3];

  temp[0] = array[0] / constant;
  temp[1] = array[1] / constant;
  temp[2] = array[2] / constant;

  return temp;
}

int * cross(int a[3], int b[3]) {
  static int temp[3];

  temp[0] = a[1] * b[2] - a[2] * b[1];
  temp[1] = a[2] * b[0] - a[0] * b[2];
  temp[2] = a[0] * b[1] - a[1] * b[0];

  return temp;
}

int norm(int a[3]) {
  return sqrt ( pow((double) a[0], 2) + pow((double) a[1], 2) + pow((double) a[2], 2) );
}

int main(int argc, char *argv[]) {
  /* Declare variables */
  FILE * outFile;
  int i, fAngle, numLines;
  int n,r,l,b,f;

  int e[3];
  int g[3];
  int tUp[3];

  int * u;
  int * v;
  int * w;

  int mvp[4][4];
  int mper[4][4];
  int mcam[4][4];

  char buffer[1024];

  /* Check argument length */
  if (argc % 4 != 0 && argc < 16) {
    usage();
  }

  /* Find number of lines needed and create arrays based on this */
  numLines = (argc - 12) / 4;
  int LINES[numLines][4];
  for (i = 0; i < numLines; i++) {
    LINES[i][0] = atoi(argv[12 + numLines*4]);
    LINES[i][1] = atoi(argv[13 + numLines*4]);
    LINES[i][2] = atoi(argv[14 + numLines*4]);
    LINES[i][3] = atoi(argv[15 + numLines*4]);
}


  /* Open output file */
  outFile = fopen(argv[1], "w");
  if (outFile == NULL) {
    fprintf(stderr, "Error, unable to open output file\n");
    exit(1);
  }

  /* Set up variables */
  e[0] = atoi(argv[2]);
  e[1] = atoi(argv[3]);
  e[2] = atoi(argv[4]);

  g[0] = atoi(argv[5]);
  g[1] = atoi(argv[6]);
  g[2] = atoi(argv[7]);

  t[0] = atoi(argv[8]);
  t[1] = atoi(argv[9]);
  t[2] = atoi(argv[10]);

  fAngle = atoi(argv[11]);

  /* Set up view matrix */
  mvp[0][0] = WIDTH/2;
  mvp[0][3] = (WIDTH-1)/2;
  mvp[1][1] = HEIGHT/2;
  mvp[1][3] = (HEIGHT-1)/2;
  mvp[2][2] = 1;
  mvp[3][3] = 1;

  /* Set up perspective matrix */
  mper[0][0] = (2 * n) / (r - l);
  mper[0][2] = (l + r) / (l - r);
  mper[1][1] = r - l;
  mper[1][2] = (2 * n) / (t - b);
  mper[1][2] = (b + t) / (b - t);
  mper[2][2] = (f + n) / (n - f);
  mper[2][3] = (2 * f * n) / (f - n);
  mper[3][3] = 1;

  /* Set up camera matrix */
  w = multVector( -1, divVector(norm(g), g) );
  u = divVector( norm(cross(t, v)), cross(t, v) );
  v = cross(w, u);

  fputs("<svg xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink' height='300px' width='300px'>\n", outFile);

  sprintf(buffer, "<line x1='-50' y1='%i' x2='50' y2='%i' stroke='#aaa' stroke-width='.5' />\n", 10, 10);
  fputs(buffer, outFile);

  fputs("</svg>", outFile);


  return 0;
}
