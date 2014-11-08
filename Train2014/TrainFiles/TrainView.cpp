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
      tw->dirty = true;
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
  if (tw->drawingTerrain->value()) {
    drawTerrain();
  }
  else {
    drawFloor(200, 10);
  }
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

  tw->dirty = false;

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
      if (tw->drawingTerrain->value())
        wi = 135;

      he = wi / aspect;
    }
    else {
      he = 110;
      if (tw->drawingTerrain->value())
        he = 135;

      wi = he*aspect;
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (!tw->drawingTerrain->value())
      glOrtho(-wi, wi, -he, he, -200, 200);
    if (tw->drawingTerrain->value())
      glOrtho(-wi, wi, -he, he, -270, 270);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(90, 1, 0, 0);
  }
  else {
    // TODO: put code for train view projection here!
    int i = tw->train_pos->value() * world->points.size();
    float t = (tw->train_pos->value() - (i * (1.0 / world->points.size()))) * world->points.size();
    
    Pnt3f pos;
    Pnt3f dir;

    // Find where to show the view based on if in parameterized space
    if (tw->arcLength->value()) {
      t = tw->train_pos->value();
      pos = genPoint(i, t, 1);
      dir = genDir(i, t, 1);
    } else {
      t = (tw->train_pos->value() - (i * (1.0 / world->points.size()))) * world->points.size();
      pos = genPoint(i, t, 0);
      dir = genDir(i, t, 0);
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(40, aspect, .1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Rotate a bit down to see the track below
    glRotatef(14, 1.0, 0, 0);
    // Rotate in the current direction that the train is facing
    glRotatef(-dir.y + 180, 0, 1.0, 0);

    glTranslatef(-pos.x, -pos.y - 10, -pos.z);
    

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

  // Since I am randomly generating trees, I am skipping shadows for simplicity
  if (tw->drawingTrees)
    drawTrees(doingShadows);
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
  tw->dirty = true;
}

void TrainView::drawTrack(bool doingShadows) {
  float size = 6;
  if (!doingShadows) {
    glColor3ub(100, 50, 0);
  }
  if (!tw->dirty) {
    if (tw->trackType->value() == 1) {
      glLineWidth(8.0);
      glBegin(GL_LINE_LOOP);
      for (int i = 0; i < trackPos.size(); i++) {
        glVertex3f(trackPos[i].x, trackPos[i].y, trackPos[i].z);
      }
      glEnd();
    } else {
      
      for (int i = 0; i < trackPos.size(); i++) {
        glPushMatrix();

        glTranslatef(trackPos[i].x, trackPos[i].y, trackPos[i].z);
        glRotatef(trackDir[i].y, 0, 1.0, 0);

        track_geom(doingShadows, size, trackPos[i].y);

        glPopMatrix();
      }
    }

  } else {
    arcTable.resize(0);
    trackPos.resize(0);
    trackDir.resize(0);
    trackLength = 0;

    glLineWidth(8.0);
    glBegin(GL_LINE_LOOP);

    // Loop through the points and calculate length of each segment
    for (int i = 0; i < world->points.size(); i++) {
      float pointLength = 0;

      for (float t = 0; t <= 1.0; t += 0.05) {
        Pnt3f P1 = genPoint(i, t, 0);
        Pnt3f P2 = genPoint(i, t + 0.01, 0);

        if (tw->trackType->value() == 1) {
          glVertex3f(P1.x, P1.y, P1.z);
          trackPos.push_back(P1);
          trackDir.push_back(genDir(i, t, 0));
        }

        float tempLength = sqrt(pow((P1.x - P2.x), 2) + pow((P1.y - P2.y), 2) + pow((P1.z - P2.z), 2));

        // Set up some variables for later when checking arc length and what points go where
        pointLength += tempLength;
        trackLength += tempLength;
        arcPoint temp;
        temp.lowDist = trackLength;
        temp.point = i;
        temp.highDist = trackLength;
        arcTable.push_back(temp);
      }

      world->points[i].length = pointLength;
    }
    glEnd();

    // If using "fancy" tracks
    if (tw->trackType->value() == 2 || tw->trackType->value() == 3) {

      float trackSpace = 5 / trackLength * tw->trackSpace->value();

      // Generate tracks for all parts of the parameterized system
      for (float j = 0; j <= 1.0; j += trackSpace) {

        int i = j * world->points.size();
        float t;

        Pnt3f pos;
        Pnt3f dir;

        if (tw->arcLength->value()) {
          t = j;
          pos = genPoint(i, t, 1);
          dir = genDir(i, t, 1);
        }
        else {
          t = (j - (i * (1.0 / world->points.size()))) * world->points.size();
          pos = genPoint(i, t, 0);
          dir = genDir(i, t, 0);
        }

        trackPos.push_back(pos);
        trackDir.push_back(dir);

        // Train tracks ties
        glPushMatrix();

        glTranslatef(pos.x, pos.y, pos.z);
        glRotatef(dir.y, 0, 1.0, 0);

        track_geom(doingShadows, size, pos.y);

        glPopMatrix();
      }
    }
  }
  
}

void TrainView::drawTrain(bool doingShadows) {
  float size = 4;
  float length = 4;

  int i = tw->train_pos->value() * world->points.size();
  float t;
  Pnt3f pos;
  Pnt3f dir;
  float frontRot;
  float backRot;

  // Calculate the position and rotation of the train
  if (tw->arcLength->value()) {
    t = tw->train_pos->value();
    pos = genPoint(i, t, 1);
    dir = genDir(i, t - 0.03, 1);

    frontRot = dir.y - genDir(i, t + 0.025, 1).y;
    backRot = dir.y - genDir(i, t - 0.045, 1).y;
  } else {
    t = (tw->train_pos->value() - (i * (1.0 / world->points.size()))) * world->points.size();
    pos = genPoint(i, t, 0);
    dir = genDir(i, t, 0);
    
    frontRot = dir.y - genDir(i, t + 0.025, 0).y;
    backRot = dir.y - genDir(i, t - 0.1, 0).y;
  }

  // If not rotating wheels, just set these angles to 0
  if (!tw->wheelRot->value())
    frontRot = backRot = 0;

  // Move and rotate the train, if necessary use arc-length parameterization
  glPushMatrix();

  glTranslatef(pos.x, pos.y + size * 2.3, pos.z);
  glRotatef(dir.y, 0, 1.0, 0);

  train_geom(doingShadows, size, length, frontRot, backRot);

  glPopMatrix();
}

void TrainView::drawTerrain() {
  float size = 250.0;
  int num = tw->samples->value();
  float step = size / (num - 1);
  vector< vector<terrainSegment> > tempTerrain(num);

  for (int i = 0; i < num; i++)
    tempTerrain[i].resize(num);

  if (!tw->dirty && terrain.size() == num * num) {
    for (int z = 0; z < num; z++) {
      for (int x = 0; x < num; x++) {
        tempTerrain[z][x].y = terrain[z * num + x].y;
        tempTerrain[z][x].c.r = terrain[z * num + x].c.r;
        tempTerrain[z][x].c.g = terrain[z * num + x].c.g;
        tempTerrain[z][x].c.b = terrain[z * num + x].c.b;
      }
    }
  } else {

    srand(tw->seed->value());

    // Generate some random y values for the terrain
    for (int z = 0; z < num; z++) {
      for (int x = 0; x < num; x++) {
        float y = rand() / (RAND_MAX / (10 * tw->roughness->value()));
        float r = 10 + rand() / (RAND_MAX / 20);
        float g = 100 + rand() / (RAND_MAX / 30);
        float b = 10 + rand() / (RAND_MAX / 20);
        
        tempTerrain[z][x].y = y;
        tempTerrain[z][x].c.r = r;
        tempTerrain[z][x].c.g = g;
        tempTerrain[z][x].c.b = b;

        terrainSegment temp;
        temp.y = y;
        temp.c.r = r;
        temp.c.g = g;
        temp.c.b = b;
        terrain.push_back(temp);
      }
    }
  }

  glPushMatrix();

  glTranslatef(-size / 2, -5, -size / 2);

  // Draw the terrain using triangle strips, find some fun random colors for each face
  for (int z = 0; z < num - 1; z++) {
    glBegin(GL_TRIANGLE_STRIP);
    for (int x = 0; x < num - 1; x++) {
      //glNormal3f(0, 1, 0);


      glColor3ub(tempTerrain[z][x].c.r, tempTerrain[z][x].c.g, tempTerrain[z][x].c.b);

      //glTexCoord2f(0.0f, 0.0f);
      glVertex3f(x * step, tempTerrain[z][x].y, z * step);

      //glTexCoord2f(1.0f, 0.0f);
      glVertex3f((x + 1) * step, tempTerrain[z][x + 1].y, z * step);

      //glTexCoord2f(0.0f, 1.0f);
      glVertex3f(x * step, tempTerrain[z + 1][x].y, (z + 1) * step);

      //glTexCoord2f(1.0f, 1.0f);
      glVertex3f((x + 1) * step, tempTerrain[z + 1][x + 1].y, (z + 1) * step);
    }
    glEnd();
  }

  glPopMatrix();
}

void TrainView::drawTrees(bool doingShadows) {
  if (tw->dirty) {
    srand(tw->seed->value());
    trees.resize(0);
    // Find places to put the trees, since there are not too many trees this should work...
    // Just in case, this generation will eventually fail and give up if it cannot find random
    // places for the trees.
    int failCount = 0;
    for (int i = 0; i < tw->numTrees->value(); i++) {
      Pnt3f pos(-999, -999, -999);
      failCount = 0;
      while (!validPos(pos) && failCount < 50) {
        pos = Pnt3f((float)rand() / (RAND_MAX / 250) - 125, (float)0, (float)rand() / (RAND_MAX / 250) - 125);
        failCount++;
      }
      if (failCount < 50) {
        tree temp;
        temp.pos = pos;
        temp.size = rand() / (RAND_MAX / 4) + 4;
        temp.c.r = 10 + rand() / (RAND_MAX / 20);
        temp.c.g = 100 + rand() / (RAND_MAX / 30);
        temp.c.b = 10 + rand() / (RAND_MAX / 20);
        trees.push_back(temp);
      }
    }
  }

  if (tw->drawingTrees->value()) {
    for (int i = 0; i < trees.size(); i++) {
      glPushMatrix();
      glTranslatef(trees[i].pos.x, trees[i].pos.y, trees[i].pos.z);
      trees_geom(doingShadows, trees[i]);
      glPopMatrix();
    }
  }
}

Pnt3f TrainView::genPoint(int i, float t, int arc) {
  double x, y, z;
  
  // If using arc length, look through the table of arc lengths to find which point and
  // parameter value to use in the next section of the point generation
  if (tw->arcLength->value() && arc == 1) {
    float dist = t * trackLength;

    for (int j = 0; j < arcTable.size(); j++) {
      if (arcTable[j].lowDist >= dist) {
        int point = arcTable[j].point;
        
        float prevLength = 0;
        for (int k = 0; k < arcTable[j].point; k++) {
          prevLength += world->points[k].length;
        }

        float u = (dist - prevLength) / world->points[point].length;
        t = u;

        if (u >= 0.99)
          u = 0.99;
        i = point;
        break;
        
      }
    }

  }
  
  // Generate using linear interpolation
  if (tw->splineBrowser->value() == 1) {
    Pnt3f P1 = world->points[(i) % (world->points.size())].pos;
    Pnt3f P2 = world->points[(i + 1) % (world->points.size())].pos;

    x = (1.0 - t) * P1.x + t * P2.x;
    y = (1.0 - t) * P1.y + t * P2.y;
    z = (1.0 - t) * P1.z + t * P2.z;
  } else if (tw->splineBrowser->value() == 2) {
    // Using cardinal cubics to generate point

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

Pnt3f TrainView::genDir(int i, float t, int arc) {
  Pnt3f P1;
  Pnt3f P2;

  // Find the direction that is being traveled for the given parameterized point

  if (arc == 1) {
    P1 = genPoint(i, t, 1);
    P2 = genPoint(i, t + 0.01, 1);
  }
  else {
    P1 = genPoint(i, t, 0);
    P2 = genPoint(i, t + 0.01, 0);
  }

  float xDir = atan2(P2.y - P1.y, P2.z - P1.z) * (180.0 / M_PI);
  float yDir = atan2(P2.x - P1.x, P2.z - P1.z) * (180.0 / M_PI);
  float zDir = atan2(P2.x - P1.x, P2.y - P1.y) * (180.0 / M_PI);

  return Pnt3f(xDir, yDir, zDir);
}

bool TrainView::validPos(Pnt3f P1) {
  float bounds;
  if (tw->drawingTerrain->value()) {
    bounds = 120;
  } else {
    bounds = 100;
  }

  float min = 20;
  // Check if point inside bounds of world
  if (P1.x < -bounds || P1.x > bounds || P1.y < -bounds || P1.y > bounds || P1.z < -bounds || P1.z > bounds)
    return false;

  // Loop through current points in the world to make sure that is is valid to place a tree
  // Do not look at the y values, at there could be an elevated track
  for (int i = 0; i < trackPos.size(); i++) {
    Pnt3f P2 = trackPos[i];
    float distance = sqrt(pow((P1.x - P2.x), 2) + pow((P1.z - P2.z), 2));
    if (distance <= min)
      return false;
  }
  
  // Check that another tree is not occupying this space
  for (int i = 0; i < trees.size(); i++) {
    Pnt3f P2 = trees[i].pos;
    float distance = sqrt(pow((P1.x - P2.x), 2) + pow((P1.z - P2.z), 2));
    if (distance <= min + trees[i].size * 2)
      return false;
  }

  return true;
}

void TrainView::train_geom(bool doingShadows, float size, float length, float frontRot, float backRot) {
  glBegin(GL_QUADS);

  float offset;

  // Slightly differnt placement of the train if arc length parameterized...
  if (tw->arcLength->value()) {
    offset = 0.5 * length;
  } else {
    offset = -length;
  }
    

  if (!doingShadows)
    glColor3ub(30, 30, 170);

  // Front
  glNormal3f(0, 0, 1);
  glVertex3f(size, size, size - offset);
  glVertex3f(-size, size, size - offset);
  glVertex3f(-size, -size, size - offset);
  glVertex3f(size, -size, size - offset);

  if (!doingShadows)
    glColor3ub(30, 170, 30);

  // Back
  glNormal3f(0, 0, -1);
  glVertex3f(size, size, -size*length - offset);
  glVertex3f(size, -size, -size*length - offset);
  glVertex3f(-size, -size, -size*length - offset);
  glVertex3f(-size, size, -size*length - offset);

  //Top
  glNormal3f(0, 1, 0);
  glVertex3f(size, size, size - offset);
  glVertex3f(-size, size, size - offset);
  glVertex3f(-size, size, -size*length - offset);
  glVertex3f(size, size, -size*length - offset);

  // Bottom
  glNormal3f(0, -1, 0);
  glVertex3f(size, -size, size - offset);
  glVertex3f(-size, -size, size - offset);
  glVertex3f(-size, -size, -size*length - offset);
  glVertex3f(size, -size, -size*length - offset);

  // Left Side
  glNormal3f(1, 0, 0);
  glVertex3f(size, size, size - offset);
  glVertex3f(size, -size, size - offset);
  glVertex3f(size, -size, -size*length - offset);
  glVertex3f(size, size, -size*length - offset);

  // Right Side
  glNormal3f(-1, 0, 0);
  glVertex3f(-size, size, size - offset);
  glVertex3f(-size, size, -size*length - offset);
  glVertex3f(-size, -size, -size*length - offset);
  glVertex3f(-size, -size, size - offset);

  glEnd();

  glPushMatrix();
  glTranslatef(0, 0, size - offset);

  if (!doingShadows)
    glColor3ub(30, 30, 170);

  GLUquadricObj *front = gluNewQuadric();
  gluCylinder(front, 5, 0, 5, 16, 3);
  glPopMatrix();
  
  
  if (!doingShadows)
    glColor3ub(175, 10, 200);

  // Draw the front wheel
  glPushMatrix();
  GLUquadricObj *wheelFront = gluNewQuadric();

  if (tw->arcLength->value()) {
    glTranslatef(-1.5 * size, -1.5 * size, -0.25 * length - offset * 1.5);
  }
  else {
    glTranslatef(-1.5 * size, -1.5 * size, -0.25 * length - offset);
  }
  
  glRotatef(90 - frontRot, 0, 1.0, 0);
  

  gluCylinder(wheelFront, size / 2, size / 2, size*3, 16, 3);
  gluDisk(wheelFront, 0, size / 2, 16, 1);
  glTranslatef(0, 0, size*3);
  gluDisk(wheelFront, 0, size / 2, 16, 1);

  glPopMatrix();

  // Draw the back wheel
  glPushMatrix();
  GLUquadricObj *wheelBack = gluNewQuadric();

  if (tw->arcLength->value()) {
    glTranslatef(-1.5 * size, -1.5 * size, -3 * length);
  } else {
    glTranslatef(-1.5 * size, -1.5 * size, -3 * length - offset * 1.5);
  }
  
  glRotatef(90 - backRot, 0, 1.0, 0);
  

  gluCylinder(wheelBack, size / 2, size / 2, size * 3, 16, 3);
  gluDisk(wheelBack, 0, size / 2, 16, 1);
  glTranslatef(0, 0, size * 3);
  gluDisk(wheelBack, 0, size / 2, 16, 1);

  glPopMatrix();
}

void TrainView::track_geom(bool doingShadows, float length, float y) {
  float size = length / 6;

  if (!doingShadows)
    glColor3ub(255, 150, 0);

  // Drawng the stilts for the given track segment if close enough to ground
  if (tw->trackType->value() == 3 && y < 25) {
    glLineWidth(8);

    glBegin(GL_LINES);
    glVertex3f(-length, size, size / 3);
    glVertex3f(-length, -y, size / 3);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(length, size, size / 3);
    glVertex3f(length, -y, size / 3);
    glEnd();
  }

  glBegin(GL_QUADS);

  // Front
  glNormal3f(0, 0, 1);
  glVertex3f(length, size, size);
  glVertex3f(-length, size, size);
  glVertex3f(-length, -size, size);
  glVertex3f(length, -size, size);

  // Back
  glNormal3f(0, 0, -1);
  glVertex3f(length, size, -size);
  glVertex3f(length, -size, -size);
  glVertex3f(-length, -size, -size);
  glVertex3f(-length, size, -size);

  //Top
  glNormal3f(0, 1, 0);
  glVertex3f(length, size, size);
  glVertex3f(-length, size, size);
  glVertex3f(-length, size, -size);
  glVertex3f(length, size, -size);

  // Bottom
  glNormal3f(0, -1, 0);
  glVertex3f(length, -size, size);
  glVertex3f(-length, -size, size);
  glVertex3f(-length, -size, -size);
  glVertex3f(length, -size, -size);

  // Left Side
  glNormal3f(1, 0, 0);
  glVertex3f(length, size, size);
  glVertex3f(length, -size, size);
  glVertex3f(length, -size, -size);
  glVertex3f(length, size, -size);

  // Right Side
  glNormal3f(-1, 0, 0);
  glVertex3f(-length, size, size);
  glVertex3f(-length, size, -size);
  glVertex3f(-length, -size, -size);
  glVertex3f(-length, -size, size);

  glEnd();

}

void TrainView::trees_geom(bool doingShadows, tree t) {
  
  glPushMatrix();

  // Orient the tree correctly
  glTranslatef(0, t.size * 3, 0);
  glRotatef(-90, 1.0, 0, 0);

  glPushMatrix();

  GLUquadricObj *top = gluNewQuadric();
  if (!doingShadows)
    glColor3ub(t.c.r, t.c.g, t.c.b);

  // Draw top of tree
  gluCylinder(top, t.size, 0, t.size * 2.5, 16, 3);
  gluDisk(top, 0, t.size, 16, 1);

  glTranslatef(0, 0, -t.size * 3);

  if (!doingShadows)
    glColor3ub(80, 40, 10);

  // Draw trunk of tree
  gluCylinder(top, t.size / 2, t.size / 2, t.size * 3, 16, 3);

  glPopMatrix();
  glPopMatrix();
}

// CVS Header - if you don't know what this is, don't worry about it
// This code tells us where the original came from in CVS
// Its a good idea to leave it as-is so we know what version of
// things you started with
// $Header: /p/course/cs559-gleicher/private/CVS/TrainFiles/TrainView.cpp,v 1.10 2009/11/08 21:34:13 gleicher Exp $
