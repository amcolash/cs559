/// GraphicsTown2006 - CS559 Sample Code
// written by Michael Gleicher - originally written Fall, 2000
//
// updated Fall 2006 - more testing code
// updated Fall 2008 - switched some internal stuff (no more linked lists)

#include "GrTown_PCH.H"
#include "GraphicsTownUI.H"
#include "FlyCamera.H"
#include "GrWorld.H"
#include "DrawUtils.H"
#include "Examples/Objects.H"
#include "Examples/SimpleBehaviors.H"
#include "Examples/Cars.H"


// for setting up shader paths and textures
#include "Utilities/ShaderTools.H"
#include "Utilities/Texture.H"


// Example code (objects and behaviors)
#include "Examples/Suburbs.H"

#include "Roads/Roads.H"
#include "Roads/Drive.H"


#include "Examples/Objects.H"
#include "Examples/Surface.h"
#include "Examples/Particle.h"
#include "Examples/Bird.h"
#include "Examples/Park.h"
#include "Examples/BirdFly.h"

#include <time.h>


// define this to get 2 cars that always turn
// #define TESTCARS

const int numCars = 100;
const int nGrids = 5;

int main(int /*argc*/, char** /*argv*/)
{

  // put in some texture paths - look all over the place
  texturePaths.push_back(".");
  texturePaths.push_back("..");
  texturePaths.push_back("Textures/signs");
  texturePaths.push_back("../Textures/signs");
  texturePaths.push_back("Textures/Textures");
  texturePaths.push_back("../Textures/Textures");
  texturePaths.push_back("Textures/Objects");
  texturePaths.push_back("../Textures/Objects");

  shaderPaths.push_back("Shaders");
  shaderPaths.push_back("../Shaders");

  // add some more stuff
  GrObject* o1 = new Church;
  o1->interesting = true;
  o1->laX = 0; o1->laY = 0; o1->laZ = 0;
  o1->lfX = -50; o1->lfY = 100; o1->lfZ = 300;
  add(o1, -100, 0, 100, pi / 2.f);


  // *****************************************************************
  //  Make your town here

  // first, some really simple things

  // cubes are particularly easy since they set their own position
  // we need to raise the cube since we're giving the position of the
  // center
  GrObject* cube1 = new ShadedCube(-50, 5, -50, 10, .7f, .6f, .3f);
  add(cube1);
  cube1->name = "Cube1";
  // make it an interesting object (so its easy to look at)
  // and give a place to look at it from
  // this is a good object to look at since it won't move
  cube1->interesting = true;
  cube1->laX = 0; cube1->laY = 0; cube1->laZ = 0;
  cube1->lfX = 70; cube1->lfY = 50; cube1->lfZ = 0;

  // make another cube - make this one spin around
  GrObject* cube2 = new Cube(-50, 5, -25, 10, .3f, .6f, .7f);
  add(cube2);
  new Spin(cube2);

  // now to demonstrate hierarchy - make another cube that spins, and
  // put a smaller cube on top of it
  GrObject* cube3 = new Cube(-50, 5, -75, 10, .7f, .3f, .6f);
  add(cube3);
  new Spin(cube3, .001f);
  GrObject* cube4 = new Cube(0, 7.5, 0, 5, 1, 0, 1);
  cube3->add(cube4);


  ////////////////////////////////////////////////////////////////////////
  // now to make a real town!
  int r, c;
  // make a 5x5 grid of town blocks - 5 houses per
  for (r = 0; r < 5; r++) {
    for (c = 0; c < 5; c++) {  
      if (r == 3 && c == 2) {
        add(new SimpleSubdivision(5, 0), static_cast<float>(r * 530), 0, static_cast<float>(c * 230));
      } else if (r == 3 && c == 3) {
        add(new SimpleSubdivision(5, 1), static_cast<float>(r * 530), 0, static_cast<float>(c * 230));
      } else {
        add(new SimpleSubdivision(5, 0), static_cast<float>(r * 530), 0, static_cast<float>(c * 230));
        add(new SimpleSubdivision(5, 1), static_cast<float>(r * 530), 0, static_cast<float>(c * 230));
      }
      add(new StraightRoad(static_cast<float>(r * 530), static_cast<float>(c * 230), static_cast<float>(r * 530 + 500), static_cast<float>(c * 230)));
    }
  }
  // make cross streets
  for (int r = 0; r <= 5; r++) {
    for (c = 0; c < 4; c++) {
      add(new StraightRoad(static_cast<float>(r * 530 - 15), static_cast<float>(c * 230 + 15), static_cast<float>(r * 530 - 15), static_cast<float>(c * 230 + 215)));
    }
  }

  // make intersections
  // make an intersection intersesting so we can look at it
  for (int r = 0; r <= 5; r++) {
    for (c = 0; c < 5; c++) {
      GrObject* g = new Intersection(static_cast<float>(r * 530 - 15), static_cast<float>(c * 230));
      if ((r == 2) && (c == 3)) {
        g->interesting = 1;
        g->name = "Intersection(2,3)";
        g->laX = static_cast<float>(r * 530 - 15);    g->laY = 0;    g->laZ = static_cast<float>(c * 230);
        g->lfX = static_cast<float>(r * 530 + 25);   g->lfY = 100;   g->lfZ = static_cast<float>(c * 230 + 150);
      }
      add(g);
    }
  }

#ifndef TESTCARS
  // add some cars
  for (int r = 0; r < 50; r++) {
    Car* c;
    switch (rand() % 3) {
    case 0: c = new Van(rand()); break;
    case 1: c = new SUV(rand()); break;
    case 2: c = new HatchBack(rand()); break;
    }
    add(c);
    new RandomDrive(c, theRoads[rand() % theRoads.size()], .2f, rand() % 2);
  }
#endif

#ifdef TESTCARS
  // two cars - one always turns right, one always turns left
  Car* c1 = new HatchBack(1);
  Car* c2 = new HatchBack(2);
  add(c1);
  add(c2);
  new RandomDrive(c1,theRoads[7],.5,0,-1);
  new RandomDrive(c2,theRoads[8],.5,0,1);

#endif

  // a race track
  Road* t = new RoundRoad(-250, 250, 100);
  add(t);
  t->name = "Track";
  t->interesting = true;
  t->laX = -250; t->laY = 0;   t->laZ = 250;
  t->lfX = -600; t->lfY = 200; t->lfZ = 450;
  // make cars go around the track
  Car* h = new HatchBack(1);
  h->name = "Race1";		// warning! we can only do this since we don't delete
  add(h);
  new SimpleDrive(h, t, 0, 0);
  h = new HatchBack(3);
  h->name = "Race2";		// warning! we can only do this since we don't delete
  add(h);
  Drive* d = new SimpleDrive(h, t, 0, 1);
  d->speed *= 2;

  /* Our new items for the world*/

  // add 40 birds
  Bird* bird1 = new Bird(0, 0, 0, 0, 0, .0);
  add(bird1);
  Bird* bird2 = new Bird(0, 0, 0, 0, 0, 0 );
  add(bird2);
  Bird* bird3 = new Bird(0, 0, 0, 0, 0, 0);
  add(bird3);
  Bird* bird4 = new Bird(0, 0, 0, 0, 0, 0);
  add(bird4);
  Bird* bird5 = new Bird(0, 0, 0, 0, 0, 0);
  add(bird5);
  Bird* bird6 = new Bird(0, 0, 0, 0, 0, 0);
  add(bird6);
  Bird* bird7 = new Bird(0, 0, 0, 0, 0, 0);
  add(bird7);
  Bird* bird8 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird9 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird10 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird11 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird12 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird13 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird14 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird15 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird16 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird17 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird18 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird19 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird20 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird21 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird22 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird23 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird24 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird25 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird26 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird27 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird28 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird29 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird30 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird31 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird32 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird33 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird34 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird35 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird36 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird37 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird38 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird39 = new Bird(0, 0, 0, 0, 0, 0);
  Bird* bird40 = new Bird(0, 0, 0, 0, 0, 0);
  add(bird8);
  add(bird9);
  add(bird10);
  add(bird11);
  add(bird12);
  add(bird13);
  add(bird14);
  add(bird15);
  add(bird16);
  add(bird17);
  add(bird18);
  add(bird19);
  add(bird20);
  add(bird21);
  add(bird22);
  add(bird23);
  add(bird24);
  add(bird25);
  add(bird26);
  add(bird27);
  add(bird28);
  add(bird29);
  add(bird30);
  add(bird31);
  add(bird32);
  add(bird33);
  add(bird34);
  add(bird35);
  add(bird36);
  add(bird37);
  add(bird38);
  add(bird39);
  add(bird40);
  new BirdFly(bird1, false);
  new BirdFly(bird2, false);
  new BirdFly(bird3, false);
  new BirdFly(bird4, false);
  new BirdFly(bird5, false);
  new BirdFly(bird6, false);
  new BirdFly(bird7, false);
  new BirdFly(bird8, false);
  new BirdFly(bird9, false);
  new BirdFly(bird10, false);
  new BirdFly(bird11, false);
  new BirdFly(bird12, false);
  new BirdFly(bird13, false);
  new BirdFly(bird14, false);
  new BirdFly(bird15, false);
  new BirdFly(bird16, false);
  new BirdFly(bird17, false);
  new BirdFly(bird18, false);
  new BirdFly(bird19, false);
  new BirdFly(bird20, false);
  new BirdFly(bird21, false);
  new BirdFly(bird22, false);
  new BirdFly(bird23, false);
  new BirdFly(bird24, false);
  new BirdFly(bird25, false);
  new BirdFly(bird26, false);
  new BirdFly(bird27, false);
  new BirdFly(bird28, false);
  new BirdFly(bird29, false);
  new BirdFly(bird30, false);
  new BirdFly(bird31, false);
  new BirdFly(bird32, false);
  new BirdFly(bird33, false);
  new BirdFly(bird34, false);
  new BirdFly(bird35, false);
  new BirdFly(bird36, false);
  new BirdFly(bird37, false);
  new BirdFly(bird38, false);
  new BirdFly(bird39, false);
  new BirdFly(bird40, true);
  //b2->interesting = true;
  //b1->interesting = true;
  //b1->name = "Bird";
  //b1->laX = 0; b1->laY = 0; 1b->laZ = -30;
  //b1->lfX = 0; b1->lfY = 15; b1->lfZ = 25;

  // Add building
  Surface* b1 = new Surface(glm::vec3(120, 0, -25), glm::vec3(0.75, 1.0, 0.75), S_BUILDING, 48,
    "ShadedCubeTest.vert", "ShadedCubeTest.frag", false);
  add(b1);

  // Add UFO
  Surface* ufo = new Surface(glm::vec3(120, 25, 15), glm::vec3(0.75, 1.0, 0.75), S_UFO, 64,
    "UFO.vert", "UFO.frag", true);
  add(ufo);

  // Add skybox
  //Skybox* skbox = new Skybox();
  //add(skbox);

  Park* p = new Park();
  add(p, 1615, 0, 500);
  p->name = "Park";
  p->interesting = true;
  p->laX = 350; p->laY = -100; p->laZ = 250;
  p->lfX = -150; p->lfY = 200; p->lfZ = -200;

  /* End our new items for the world */


  // *****************************************************************
  // now make a UI
  FlyCamera* fc = new FlyCamera;
  Map* m = new Map;

  // Rotate camera on startup (to look at something interesting)
  fc->direction = -90.0 * (3.1415926535 / 180.0);

  add(fc);
  add(m);

  GraphicsTownUI grTown;
  grTown.make_window();
  grTown.townView->defaultCamera = fc;
  grTown.window->show();

  Fl::run();
  return 1;
}

// $Header: /p/course/cs559-gleicher/private/CVS/GrTown/Main.cpp,v 1.8 2009/11/10 22:40:03 gleicher Exp $
