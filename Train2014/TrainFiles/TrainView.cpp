// CS559 Train Project
// TrainView class implementation
// see the header for details
// look for TODO: to see things you want to add/change
// 

#include "TrainView.H"
#include "TrainWindow.H"

#include "Utilities/3DUtils.H"

#include <Fl/fl.h>

#define _USE_MATH_DEFINES // for C++
#include <math.h>

// we will need OpenGL, and OpenGL needs windows.h
#include <windows.h>
#include "GL/gl.h"
#include "GL/glu.h"

#ifdef EXAMPLE_SOLUTION
#include "TrainExample/TrainExample.H"
#endif


TrainView::TrainView(int x, int y, int w, int h, const char* l) : Fl_Gl_Window(x, y, w, h, l)
{
  mode(FL_RGB | FL_ALPHA | FL_DOUBLE | FL_STENCIL);

  resetArcball();
}

void TrainView::resetArcball()
{
  // set up the camera to look at the world
  // these parameters might seem magical, and they kindof are
  // a little trial and error goes a long way
  arcball.setup(this, 40, 250, .2f, .4f, 0);
}

// FlTk Event handler for the window
// TODO: if you want to make the train respond to other events 
// (like key presses), you might want to hack this.
int TrainView::handle(int event)
{
  // see if the ArcBall will handle the event - if it does, then we're done
  // note: the arcball only gets the event if we're in world view
  if (tw->worldCam->value())
    if (arcball.handle(event)) return 1;

  // remember what button was used
  static int last_push;

  switch (event) {
  case FL_PUSH:
    last_push = Fl::event_button();
    if (last_push == 1) {
      doPick();
      damage(1);
      return 1;
    };
    break;
  case FL_RELEASE:
    damage(1);
    last_push = 0;
    return 1;
  case FL_DRAG:
    if ((last_push == 1) && (selectedCube >= 0)) {
      ControlPoint* cp = &world->points[selectedCube];

      double r1x, r1y, r1z, r2x, r2y, r2z;
      getMouseLine(r1x, r1y, r1z, r2x, r2y, r2z);

      double rx, ry, rz;
      mousePoleGo(r1x, r1y, r1z, r2x, r2y, r2z,
        static_cast<double>(cp->pos.x),
        static_cast<double>(cp->pos.y),
        static_cast<double>(cp->pos.z),
        rx, ry, rz,
        (Fl::event_state() & FL_CTRL) != 0);
      cp->pos.x = (float)rx;
      cp->pos.y = (float)ry;
      cp->pos.z = (float)rz;
      damage(1);
    }
    break;
    // in order to get keyboard events, we need to accept focus
  case FL_FOCUS:
    return 1;
  case FL_ENTER:	// every time the mouse enters this window, aggressively take focus
    focus(this);
    break;
  case FL_KEYBOARD:
    int k = Fl::event_key();
    int ks = Fl::event_state();
    if (k == 'p') {
      if (selectedCube >= 0)
        printf("Selected(%d) (%g %g %g) (%g %g %g)\n", selectedCube,
        world->points[selectedCube].pos.x, world->points[selectedCube].pos.y, world->points[selectedCube].pos.z,
        world->points[selectedCube].orient.x, world->points[selectedCube].orient.y, world->points[selectedCube].orient.z);
      else
        printf("Nothing Selected\n");
      return 1;
    };
    break;
  }

  return Fl_Gl_Window::handle(event);
}

// this is the code that actually draws the window
// it puts a lot of the work into other routines to simplify things
void TrainView::draw()
{

  glViewport(0, 0, w(), h());

  // clear the window, be sure to clear the Z-Buffer too
  glClearColor(0, 0, .3f, 0);		// background should be blue
  // we need to clear out the stencil buffer since we'll use
  // it for shadows
  glClearStencil(0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glEnable(GL_DEPTH);

  // Blayne prefers GL_DIFFUSE
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

  // prepare for projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  setProjection();		// put the code to set up matrices here

  // TODO: you might want to set the lighting up differently
  // if you do, 
  // we need to set up the lights AFTER setting up the projection

  // enable the lighting
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  // top view only needs one light
  if (tw->topCam->value()) {
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
  }
  else {
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
  }
  // set the light parameters
  GLfloat lightPosition1[] = { 0, 1, 1, 0 }; // {50, 200.0, 50, 1.0};
  GLfloat lightPosition2[] = { 1, 0, 0, 0 };
  GLfloat lightPosition3[] = { 0, -1, 0, 0 };
  GLfloat yellowLight[] = { 0.5f, 0.5f, .1f, 1.0 };
  GLfloat whiteLight[] = { 1.0f, 1.0f, 1.0f, 1.0 };
  GLfloat blueLight[] = { .1f, .1f, .3f, 1.0 };
  GLfloat grayLight[] = { .3f, .3f, .3f, 1.0 };

  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition1);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
  glLightfv(GL_LIGHT0, GL_AMBIENT, grayLight);

  glLightfv(GL_LIGHT1, GL_POSITION, lightPosition2);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, yellowLight);

  glLightfv(GL_LIGHT2, GL_POSITION, lightPosition3);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, blueLight);



  // now draw the ground plane
  setupFloor();
  glDisable(GL_LIGHTING);
  drawFloor(200, 10);
  glEnable(GL_LIGHTING);
  setupObjects();

  // we draw everything twice - once for real, and then once for
  // shadows
  drawStuff();

  // this time drawing is for shadows (except for top view)
  if (!tw->topCam->value()) {
    setupShadows();
    drawStuff(true);
    unsetupShadows();
  }

}

// note: this sets up both the Projection and the ModelView matrices
// HOWEVER: it doesn't clear the projection first (the caller handles
// that) - its important for picking
void TrainView::setProjection()
{
  // compute the aspect ratio (we'll need it)
  float aspect = static_cast<float>(w()) / static_cast<float>(h());

  if (tw->worldCam->value())
    arcball.setProjection(false);
  else if (tw->topCam->value()) {
    float wi, he;
    if (aspect >= 1) {
      wi = 110;
      he = wi / aspect;
    }
    else {
      he = 110;
      wi = he*aspect;
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-wi, wi, -he, he, -200, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(90, 1, 0, 0);
  }
  else {
    // TODO: put code for train view projection here!
    printf("i was called\n");
    int i = tw->train_pos->value() * world->points.size();
    float t = (tw->train_pos->value() - (i * (1.0 / world->points.size()))) * world->points.size();
    Pnt3f pos = genPoint(i, t, 1, 0);
    Pnt3f rot = genDir(i, t);

    tw->eyeX->value(-pos.x);
    tw->eyeY->value(-pos.y);
    tw->eyeZ->value(-pos.z);
    tw->rotY->value(rot.y);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(40, aspect, .1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //glRotatef(tw->rotY->value(), 0, 1, 0);

    glRotatef(tw->rotZ->value(), 1, 0, 0);
    glRotatef(-tw->rotY->value() + 180, 0, 1, 0);

    glTranslatef(tw->eyeX->value(), tw->eyeY->value() - 10, tw->eyeZ->value());
    

#ifdef EXAMPLE_SOLUTION
    trainCamView(this,aspect);
#endif
  }
}

// this draws all of the stuff in the world
// NOTE: if you're drawing shadows, DO NOT set colors 
// (otherwise, you get colored shadows)
// this gets called twice per draw - once for the objects, once for the shadows
// TODO: if you have other objects in the world, make sure to draw them
void TrainView::drawStuff(bool doingShadows)
{
  // draw the control points
  // don't draw the control points if you're driving 
  // (otherwise you get sea-sick as you drive through them)
  if (!tw->trainCam->value()) {
    for (size_t i = 0; i < world->points.size(); ++i) {
      if (!doingShadows) {
        if (((int)i) != selectedCube)
          glColor3ub(240, 60, 60);
        else
          glColor3ub(240, 240, 30);
      }
      world->points[i].draw();
    }
  }

  // TODO: call your own track drawing code
  drawTrack(doingShadows);
#ifdef EXAMPLE_SOLUTION
  drawTrack(this, doingShadows);
#endif

  // draw the train
  // TODO: call your own train drawing code
  if (!tw->trainCam->value())
    drawTrain(doingShadows);
#ifdef EXAMPLE_SOLUTION
  // don't draw the train if you're looking out the front window
  if (!tw->trainCam->value())
    drawTrain(this, doingShadows);
#endif
}

// this tries to see which control point is under the mouse
// (for when the mouse is clicked)
// it uses OpenGL picking - which is always a trick
// TODO: if you want to pick things other than control points, or you
// changed how control points are drawn, you might need to change this
void TrainView::doPick()
{
  make_current();		// since we'll need to do some GL stuff

  int mx = Fl::event_x(); // where is the mouse?
  int my = Fl::event_y();

  // get the viewport - most reliable way to turn mouse coords into GL coords
  int viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  // set up the pick matrix on the stack - remember, FlTk is
  // upside down!
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPickMatrix((double)mx, (double)(viewport[3] - my), 5, 5, viewport);

  // now set up the projection
  setProjection();

  // now draw the objects - but really only see what we hit
  GLuint buf[100];
  glSelectBuffer(100, buf);
  glRenderMode(GL_SELECT);
  glInitNames();
  glPushName(0);

  // draw the cubes, loading the names as we go
  for (size_t i = 0; i < world->points.size(); ++i) {
    glLoadName((GLuint)(i + 1));
    world->points[i].draw();
  }

  // go back to drawing mode, and see how picking did
  int hits = glRenderMode(GL_RENDER);
  if (hits) {
    // warning; this just grabs the first object hit - if there
    // are multiple objects, you really want to pick the closest
    // one - see the OpenGL manual 
    // remember: we load names that are one more than the index
    selectedCube = buf[3] - 1;
  }
  else // nothing hit, nothing selected
    selectedCube = -1;

  printf("Selected Cube %d\n", selectedCube);
}

void TrainView::drawTrack(bool doingShadows) {
  if (!doingShadows) {
    glColor3ub(100, 50, 0);
  }

  vector<Pnt3f> tracks;

  arcTable.resize(0);
  trackLength = 0;

  glLineWidth(5.0);
  glBegin(GL_LINE_LOOP);

  // Loop through the points and calculate each segment
  for (int i = 0; i < world->points.size(); i++) {
    float pointLength = 0;

    for (float t = 0; t <= 1.0; t += 0.05) {
      Pnt3f P1 = genPoint(i, t, 0, 0);
      Pnt3f P2 = genPoint(i, t + 0.01, 0, 0);
      //glVertex3f(P1.x, P1.y, P1.z);

      float tempLength = sqrt(pow((P1.x - P2.x), 2) + pow((P1.y - P2.y), 2) + pow((P1.z - P2.z), 2));

      pointLength += tempLength;
      trackLength += tempLength;
      arcPoint temp;
      temp.lowDist = trackLength;
      temp.point = i;
      temp.highDist = trackLength;
      arcTable.push_back(temp);
    }

    world->points[i].length = pointLength;
    //printf("control point(%d): (%f, %f, %f) %f\n", i, pointLength, world->points[i].pos.x, world->points[i].pos.y, world->points[i].pos.z);
  }
  glEnd();


  //glPushMatrix();
  //glRotatef(90, 0, 1, 0);
  for (float j = 0; j <= 1.0; j += 0.01) {
    glBegin(GL_LINES);
    
    int i = j * world->points.size();
    float t = (j - (i * (1.0 / world->points.size()))) * world->points.size();
    Pnt3f temp = genPoint(i, t, 1, 1);
    Pnt3f dir = genDir(i, t);
    glRotatef(dir.y, 0, 1.0, 0);

    printf("t: %f, Point: (%f, %f, %f), dir: %f\n", t, temp.x, temp.y, temp.z, dir.y);

    glVertex3f(temp.x + 5, temp.y, temp.z);
    glVertex3f(temp.x - 5, temp.y, temp.z);

    glEnd();

    /*
    float cx = (P1.x + P2.x) / 2;
    float cy = (P1.y + P2.y) / 2;

    float track1x = ((P1.x - cx) * cos(90) + (P1.y - cy) * sin(90)) + cx;
    float track1y = ((P1.x - cx) * sin(90) + (P1.y - cy) * cos(90)) + cy;

    float track2x = ((P2.x - cx) * cos(90) + (P2.y - cy) * sin(90)) + cx;
    float track2y = ((P2.x - cx) * sin(90) + (P2.y - cy) * cos(90)) + cy;
    */
  }
  //glPopMatrix();

}

void TrainView::drawTrain(bool doingShadows) {
  float size = 4;
  float length = 3;

  glPushMatrix();

  int i = tw->train_pos->value() * world->points.size();
  float t = (tw->train_pos->value() - (i * (1.0 / world->points.size()))) * world->points.size();
  Pnt3f temp = genPoint(i, t, 1, 0);

  glTranslatef(temp.x, temp.y + size, temp.z);
  glRotatef(genDir(i, t).y, 0, 1.0, 0);

  train_geom(doingShadows, size, length);

  glPopMatrix();
}

Pnt3f TrainView::genPoint(int i, float t, int arc, int special) {
  double x, y, z;
  
  if (tw->arcLength->value() && arc == 1) {
    float dist = tw->train_pos->value() * trackLength;

    if (special == 1)
      dist = (tw->train_pos->value() + 0.01) * trackLength;

    for (int j = 0; j < arcTable.size(); j++) {
      if (arcTable[j].lowDist >= dist) {
        int point = arcTable[j].point;
        //printf("j: %d, found point (%d), dist: %f, current: %d\n", j, point, dist, i);
        
        float prevLength = 0;
        for (int k = 0; k < arcTable[j].point; k++) {
          prevLength += world->points[k].length;
        }

        float u = (dist - prevLength) / world->points[point].length;
        //printf("dist - prev / ptLength = u: %f - %f / %f = %f\n", dist, prevLength, world->points[point].length, u);
        t = u;

        if (u >= 0.99)
          u = 0.99;
        i = point;
        break;
        
      }
    }

  }
  
  if (tw->splineBrowser->value() == 1) {
    Pnt3f P1 = world->points[(i) % (world->points.size())].pos;
    Pnt3f P2 = world->points[(i + 1) % (world->points.size())].pos;

    x = (1.0 - t) * P1.x + t * P2.x;
    y = (1.0 - t) * P1.y + t * P2.y;
    z = (1.0 - t) * P1.z + t * P2.z;
  } else {
    Pnt3f P1 = world->points[(i - 1) % (world->points.size())].pos;
    Pnt3f P2 = world->points[(i) % (world->points.size())].pos;
    Pnt3f P3 = world->points[(i + 1) % (world->points.size())].pos;
    Pnt3f P4 = world->points[(i + 2) % (world->points.size())].pos;

    double t2 = t*t;
    double t3 = t*t*t;

    x = 0.5 * ((2 * P2.x) + (-P1.x + P3.x) * t + (2 * P1.x - 5 * P2.x + 4 * P3.x - P4.x)
      * t2 + (-P1.x + 3 * P2.x - 3 * P3.x + P4.x) * t3);
    y = 0.5 * ((2 * P2.y) + (-P1.y + P3.y) * t + (2 * P1.y - 5 * P2.y + 4 * P3.y - P4.y)
      * t2 + (-P1.y + 3 * P2.y - 3 * P3.y + P4.y) * t3);
    z = 0.5 * ((2 * P2.z) + (-P1.z + P3.z) * t + (2 * P1.z - 5 * P2.z + 4 * P3.z - P4.z)
      * t2 + (-P1.z + 3 * P2.z - 3 * P3.z + P4.z) * t3);
  }

  return Pnt3f((float)x, (float)y, (float)z);
}

Pnt3f TrainView::genDir(int i, float t) {
  Pnt3f P1 = genPoint(i, t, 1, 0);
  Pnt3f P2 = genPoint(i, t + 0.01, 1, 1);

  float xDir = atan2(P2.y - P1.y, P2.z - P1.z) * (180.0 / M_PI);
  float yDir = atan2(P2.x - P1.x, P2.z - P1.z) * (180.0 / M_PI);
  float zDir = atan2(P2.x - P1.x, P2.y - P1.y) * (180.0 / M_PI);

  //printf("(%f, %f, %f), (%f, %f, %f)\n", P1.x, P1.y, P1.z, P2.x, P2.y, P2.z);
  //printf("x: %f, y: %f, z: %f\n", xDir, yDir, zDir);

  return Pnt3f(xDir, yDir, zDir);
}

void TrainView::train_geom(bool doingShadows, float size, float length) {
  glBegin(GL_QUADS);

  if (!doingShadows)
    glColor3ub(30, 30, 170);

  // Front
  glNormal3f(0, 0, 1);
  glVertex3f(size, size, size);
  glVertex3f(-size, size, size);
  glVertex3f(-size, -size, size);
  glVertex3f(size, -size, size);

  if (!doingShadows)
    glColor3ub(30, 170, 30);

  // Back
  glNormal3f(0, 0, -1);
  glVertex3f(size, size, -size*length);
  glVertex3f(size, -size, -size*length);
  glVertex3f(-size, -size, -size*length);
  glVertex3f(-size, size, -size*length);

  //Top
  glNormal3f(0, 1, 0);
  glVertex3f(size, size, size);
  glVertex3f(-size, size, size);
  glVertex3f(-size, size, -size*length);
  glVertex3f(size, size, -size*length);

  // Bottom
  glNormal3f(0, -1, 0);
  glVertex3f(size, -size, size);
  glVertex3f(-size, -size, size);
  glVertex3f(-size, -size, -size*length);
  glVertex3f(size, -size, -size*length);

  // Left Side
  glNormal3f(1, 0, 0);
  glVertex3f(size, size, size);
  glVertex3f(size, -size, size);
  glVertex3f(size, -size, -size*length);
  glVertex3f(size, size, -size*length);

  // Right Side
  glNormal3f(-1, 0, 0);
  glVertex3f(-size, size, size);
  glVertex3f(-size, size, -size*length);
  glVertex3f(-size, -size, -size*length);
  glVertex3f(-size, -size, size);

  glEnd();

  glPushMatrix();
  glTranslatef(0, 0, size);

  if (!doingShadows)
    glColor3ub(30, 30, 170);

  GLUquadricObj *quadObj = gluNewQuadric();
  gluCylinder(quadObj, 5, 0, 5, 16, 3);

  glPopMatrix();

}

// CVS Header - if you don't know what this is, don't worry about it
// This code tells us where the original came from in CVS
// Its a good idea to leave it as-is so we know what version of
// things you started with
// $Header: /p/course/cs559-gleicher/private/CVS/TrainFiles/TrainView.cpp,v 1.10 2009/11/08 21:34:13 gleicher Exp $
