// HW2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <random>
#include <fstream>
#include <array>
#include <vector>

using namespace std;

/////////////////////////////////////////////////
//////////////// GRID STUFF /////////////////////
/////////////////////////////////////////////////

class domain {																															// Creates the Gridworld and goal coordinates
public:
	void init();

};

void domain::init() {
	int x;																																// Horizontal dimension for GRID
	int y;																																// Vertical dimension for GRID
	
}

////////////////////////////////////////////////
////////////////// AGENT STUFF /////////////////
////////////////////////////////////////////////

class agent {
public:
	int ax;																																// Agent's x coordinate
	int ay;																																// Agent's y coordinate
	int last_ax;																														// Former x coordinate
	int last_ay;																														// Former y coordinate
	void init();																														// Initialize starting coordinates
	void up();																															// Move agent up one cell
	void down();																														// Move agent down one cell
	void right();																														// Move agent right one cell
	void left();																														// Move agent left one cell
};

void agent::init() {

}


void agent::up() {																														// ay + 1

}

void agent::down() {																													// ay - 1

}

void agent::right() {																													// ax + 1

}

void agent::left() {																													// ax - 1

}

////////////////////////////////////////////////
///////////////// BUMP FUNCTIONS ///////////////
////////////////////////////////////////////////

void bump() {																															// To be used if the learner moves off the Gridworld

}

void bump_extreme() {																													// To be used if the learner's initial coordinates are off the charts

}

///////////////////////////////////////////////
//////////////// TEST FUNCTIONS ///////////////
///////////////////////////////////////////////

void testA() {																															// Relocation of agent when extreme initial coordinates are used
	// check the difference of ax,ay and the max_x, max_y
	// designate ax,ay - difference x,y
	// use bump_extreme??

}

void testB() {																															// Human navigation

}

void testC() {																															// Heuristic navigation

}

///////////////////////////////////////////////

int main()
{
	srand(time(NULL));


    return 0;
}

