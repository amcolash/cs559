// CS559 Train Project -
// Train Window class implementation
// - note: this is code that a student might want to modify for their project
//   see the header file for more details
// - look for the TODO: in this file
// - also, look at the "TrainView" - its the actual OpenGL window that
//   we draw into
//
// Written by Mike Gleicher, October 2008
//

#include "TrainWindow.H"
#include "TrainView.H"
#include "CallBacks.H"

#include <FL/fl.h>
#include <FL/Fl_Box.h>

// for using the real time clock
#include <time.h>



/////////////////////////////////////////////////////
TrainWindow::TrainWindow(const int x, const int y) : Fl_Double_Window(x,y,800,600,"Train and Roller Coaster")
{
	// make all of the widgets
	begin();	// add to this widget
	{
		int pty=5;			// where the last widgets were drawn

		trainView = new TrainView(5,5,590,590);
		trainView->tw = this;
		trainView->world = &world;
		this->resizable(trainView);

		// to make resizing work better, put all the widgets in a group
		widgets = new Fl_Group(600,5,190,590);
		widgets->begin();

		runButton = new Fl_Button(605,pty,60,20,"Run");
		togglify(runButton);

		Fl_Button* fb = new Fl_Button(700,pty,25,20,"@>>");
		fb->callback((Fl_Callback*)forwCB,this);
		Fl_Button* rb = new Fl_Button(670,pty,25,20,"@<<");
		rb->callback((Fl_Callback*)backCB,this);
		
		arcLength = new Fl_Button(730,pty,65,20,"ArcLength");
    arcLength->callback((Fl_Callback*)dirtyCB, this);
		togglify(arcLength,1);
  
		pty+=25;
		speed = new Fl_Value_Slider(655,pty,140,20,"Speed");
		speed->range(0,5);
		speed->value(1);
		speed->align(FL_ALIGN_LEFT);
		speed->type(FL_HORIZONTAL);

    pty += 30;

    // Position slider to control where the train is
    train_pos = new Fl_Value_Slider(655, pty, 140, 20, "Position");
    train_pos->range(0, 1);
    train_pos->value(0);
    train_pos->align(FL_ALIGN_LEFT);
    train_pos->type(FL_HORIZONTAL);
    train_pos->callback((Fl_Callback*)damageCB, this);

    pty += 30;

    // Toggle for rotation of wheels independent of train body
    wheelRot = new Fl_Button(605, pty, 190, 20, "Independent Wheel Rotation");
    togglify(wheelRot, 1);

    pty += 25;

    // Spacing for the track rails
    trackSpace = new Fl_Value_Slider(655, pty, 140, 20, "Spacing");
    trackSpace->range(0.1, 1);
    trackSpace->value(0.4);
    trackSpace->align(FL_ALIGN_LEFT);
    trackSpace->type(FL_HORIZONTAL);
    trackSpace->callback((Fl_Callback*)dirtyCB, this);

    pty += 30;

		// camera buttons - in a radio button group
		Fl_Group* camGroup = new Fl_Group(600,pty,195,20);
		camGroup->begin();
		worldCam = new Fl_Button(605, pty, 60, 20, "World");
        worldCam->type(FL_RADIO_BUTTON);		// radio button
        worldCam->value(1);			// turned on
        worldCam->selection_color((Fl_Color)3); // yellow when pressed
		worldCam->callback((Fl_Callback*)damageCB,this);
		trainCam = new Fl_Button(670, pty, 60, 20, "Train");
        trainCam->type(FL_RADIO_BUTTON);
        trainCam->value(0);
        trainCam->selection_color((Fl_Color)3);
		trainCam->callback((Fl_Callback*)damageCB,this);
		topCam = new Fl_Button(735, pty, 60, 20, "Top");
        topCam->type(FL_RADIO_BUTTON);
        topCam->value(0);
        topCam->selection_color((Fl_Color)3);
		topCam->callback((Fl_Callback*)damageCB,this);
		camGroup->end();

		pty += 30;

		// browser to select spline types
		// TODO: make sure these choices are the same as what the code supports
		splineBrowser = new Fl_Browser(605,pty,120,55,"Spline Type");
		splineBrowser->type(2);		// select
		splineBrowser->callback((Fl_Callback*)dirtyCB,this);
		splineBrowser->add("Linear");
		splineBrowser->add("Cardinal Cubic");
		//splineBrowser->add("Cubic B-Spline");
		splineBrowser->select(2);

    pty += 85;
    
    // browser to select track types
    trackType = new Fl_Browser(605, pty, 120, 70, "Track Type");
    trackType->type(2);		// select
    trackType->callback((Fl_Callback*)dirtyCB, this);
    trackType->add("Simple Line");
    trackType->add("3d Rails");
    trackType->add("Rails + Stilts");
    trackType->select(3);

		pty += 100;

		// add and delete points
		Fl_Button* ap = new Fl_Button(605,pty,80,20,"Add Point");
		ap->callback((Fl_Callback*)addPointCB,this);
		Fl_Button* dp = new Fl_Button(690,pty,80,20,"Delete Point");
		dp->callback((Fl_Callback*)deletePointCB,this);

		pty += 25;

		// reset the points
		resetButton = new Fl_Button(735,pty,60,20,"Reset");
		resetButton->callback((Fl_Callback*)resetCB,this);
		Fl_Button* loadb = new Fl_Button(605,pty,60,20,"Load");
		loadb->callback((Fl_Callback*) loadCB, this);
		Fl_Button* saveb = new Fl_Button(670,pty,60,20,"Save");
		saveb->callback((Fl_Callback*) saveCB, this);

		pty += 35;

    /*
		// roll the points
		Fl_Button* rx = new Fl_Button(605,pty,30,20,"R+X");
		rx->callback((Fl_Callback*)rpxCB,this);
		Fl_Button* rxp = new Fl_Button(635,pty,30,20,"R-X");
		rxp->callback((Fl_Callback*)rmxCB,this);
		Fl_Button* rz = new Fl_Button(670,pty,30,20,"R+Z");
		rz->callback((Fl_Callback*)rpzCB,this);
		Fl_Button* rzp = new Fl_Button(700,pty,30,20,"R-Z");
		rzp->callback((Fl_Callback*)rmzCB,this);

		pty+=30;
    */


    // Widgets below are for custom terrain and environment settings
    
    // Toggle for drawing random trees
    drawingTrees = new Fl_Button(600, pty, 80, 20, "Draw Trees");
    togglify(drawingTrees, 1);
    drawingTrees->callback((Fl_Callback*)dirtyCB, this);

    // Toggle for random terrain generation
    drawingTerrain = new Fl_Button(683, pty, 115, 20, "Random Terrain");
    togglify(drawingTerrain, 1);
    drawingTerrain->callback((Fl_Callback*)dirtyCB, this);

    pty += 35;

    // Seed for pseudo-randomness
    seed = new Fl_Value_Slider(655, pty, 140, 20, "Seed");
    seed->range(0, 1000);
    seed->value(0);
    seed->align(FL_ALIGN_LEFT);
    seed->type(FL_HORIZONTAL);
    seed->callback((Fl_Callback*)dirtyCB, this);

    pty += 30;

    // Amount of noise (randomness) for terrain generation
    roughness = new Fl_Value_Slider(655, pty, 140, 20, "Noise");
    roughness->range(0, 1);
    roughness->value(0.75);
    roughness->align(FL_ALIGN_LEFT);
    roughness->type(FL_HORIZONTAL);
    roughness->callback((Fl_Callback*)dirtyCB, this);

    pty += 30;

    // Number of subdivisons when generating terrain
    samples = new Fl_Value_Slider(655, pty, 140, 20, "Samples");
    samples->range(2, 70);
    samples->value(30);
    samples->align(FL_ALIGN_LEFT);
    samples->type(FL_HORIZONTAL);
    samples->callback((Fl_Callback*)dirtyCB, this);

    pty += 30;

    // Number of trees to be generated
    numTrees = new Fl_Value_Slider(655, pty, 140, 20, "Trees");
    numTrees->range(1, 50);
    numTrees->value(30);
    numTrees->align(FL_ALIGN_LEFT);
    numTrees->type(FL_HORIZONTAL);
    numTrees->callback((Fl_Callback*)dirtyCB, this);

		// TODO: add widgets for all of your fancier features here
#ifdef EXAMPLE_SOLUTION
		makeExampleWidgets(this,pty);
#endif

		// we need to make a little phantom widget to have things resize correctly
		Fl_Box* resizebox = new Fl_Box(600,595,200,5);
		widgets->resizable(resizebox);

		widgets->end();
	}
	end();	// done adding to this widget

	// set up callback on idle
	Fl::add_idle((void (*)(void*))runButtonCB,this);
}

// handy utility to make a button into a toggle
void TrainWindow::togglify(Fl_Button* b, int val)
{
    b->type(FL_TOGGLE_BUTTON);		// toggle
    b->value(val);		// turned off
    b->selection_color((Fl_Color)3); // yellow when pressed	
	  b->callback((Fl_Callback*)damageCB,this);
}

void TrainWindow::damageMe()
{
	if (trainView->selectedCube >= ((int)world.points.size()))
		trainView->selectedCube = 0;
	trainView->damage(1);
}

/////////////////////////////////////////////////////
// this will get called (approximately) 30 times per second
// if the run button is pressed
void TrainWindow::advanceTrain(float dir)
{
  dir = dir / 2;
  float value = fmodf(train_pos->value() + dir * speed->value(), 1.0);
  if (value < 0)
    value += 1.0;

  train_pos->value ( (double) value );

	// TODO: make this work for your train
#ifdef EXAMPLE_SOLUTION
	// note - we give a little bit more example code here than normal,
	// so you can see how this works

	if (arcLength->value()) {
		float vel = ew.physics->value() ? physicsSpeed(this) * (float)speed->value() : dir * (float)speed->value();
		world.trainU += arclenVtoV(world.trainU, vel, this);
	} else {
		world.trainU +=  dir * ((float)speed->value() * .1f);
	}

	float nct = static_cast<float>(world.points.size());
	if (world.trainU > nct) world.trainU -= nct;
	if (world.trainU < 0) world.trainU += nct;
#endif
}