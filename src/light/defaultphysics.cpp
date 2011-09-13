
#include <GL/gl.h>
#include "defaultphysics.hpp"


/**
 * TODO: currently this just simulates the ode demo "demo_chain1.c"
 * we still actually have to hook it up to the objects in the display.
 */

/* some constants */

#define NUM 10			/* number of boxes */
#define SIDE (0.2)		/* side length of a box */
#define MASS (1.0)		/* mass of a box */
#define RADIUS (0.1732f)	/* sphere radius */


/* dynamics and collision objects */

static dWorldID world;
static dSpaceID space;
static dBodyID body[NUM];
static dJointID joint[NUM-1];
static dJointGroupID contactgroup;
static dGeomID sphere[NUM];

static void initWorld();
static void nearCallback (void *data, dGeomID o1, dGeomID o2);
static void simLoop (int pause);
static void createObjects(PDisplay display);
static void destroyWorld();

DefaultPhysics::DefaultPhysics(){

}

void DefaultPhysics::onLoop(){

	simLoop(false);
}

void DefaultPhysics::setDisplay(PDisplay display){

	assert(display);

	this->display = display;

}

void DefaultPhysics::init(){


	assert(display);
	initWorld();
	createObjects(display);
	dAllocateODEDataForThread(dAllocateMaskAll);

}

void DefaultPhysics::cleanUp(){

	destroyWorld();

}

void DefaultPhysics::onEvent(SDL_Event* event){

	switch(event->type){

		case SDL_MOUSEMOTION:
			display->rotateScene(5.0,0.f,1.f,0.f);
			break;

	}

}
/**
 * Initialises the ODE world
 */
static void initWorld(){

	dInitODE2(0);
	world = dWorldCreate();
	space = dHashSpaceCreate (0);
	contactgroup = dJointGroupCreate (1000000);
	dWorldSetGravity (world,0,0,-0.5);
	dCreatePlane (space,0,0,1,0);


}


// this is called by dSpaceCollide when two objects in space are
// potentially colliding.
static void nearCallback (void *data, dGeomID o1, dGeomID o2){

	/* exit without doing anything if the two bodies are connected by a joint */
	  dBodyID b1,b2;
	  dContact contact;

	  b1 = dGeomGetBody(o1);
	  b2 = dGeomGetBody(o2);
	  if (b1 && b2 && dAreConnected (b1,b2)) return;

	  contact.surface.mode = 0;
	  contact.surface.mu = 0.1;
	  contact.surface.mu2 = 0;
	  if (dCollide (o1,o2,1,&contact.geom,sizeof(dContactGeom))) {
	    dJointID c = dJointCreateContact (world,contactgroup,&contact);
	    dJointAttach (c,b1,b2);
	  }

	}

	// simulation loop
	static void simLoop (int pause)	{

		  if (!pause) {
		    static double angle = 0;
		    angle += 0.05;
		    dBodyAddForce (body[NUM-1],0,0,1.5*(sin(angle)+1.0));

		    dSpaceCollide (space,0,&nearCallback);
		    dWorldStep (world,0.05);

		    /* remove all contact joints */
		    dJointGroupEmpty (contactgroup);
		  }
		  	    //TODO: call display draw
	}

	static void createObjects(PDisplay display){

		//	 display->getNodeNames();
		//	 display->getCollisionGeometryForNode();

		  int i;
		  dReal k;
		  dMass m;


		 for (i=0; i<NUM; i++) {
		    body[i] = dBodyCreate (world);
		    k = i*SIDE;
		    dBodySetPosition (body[i],k,k,k+0.4);
		    dMassSetBox (&m,1,SIDE,SIDE,SIDE);
		    dMassAdjust (&m,MASS);
		    dBodySetMass (body[i],&m);
		    sphere[i] = dCreateSphere (space,RADIUS);
		    dGeomSetBody (sphere[i],body[i]);
		  }
		  for (i=0; i<(NUM-1); i++) {
		    joint[i] = dJointCreateBall (world,0);
		    dJointAttach (joint[i],body[i],body[i+1]);
		    k = (i+0.5)*SIDE;
		    dJointSetBallAnchor (joint[i],k,k,k+0.4);
		  }


	}

	/**
	 * destroys and cleans up ode
	 */
	static void destroyWorld(){

		  dJointGroupDestroy (contactgroup);
		  dSpaceDestroy (space);
		  dWorldDestroy (world);
		  dCloseODE();

	}


