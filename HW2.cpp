// HW2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include <array>
#include <string.h>

using namespace std;

/////////////////////////////////////////////////
/////////////// AGENT STUFF /////////////////////
/////////////////////////////////////////////////

class agent {
public:
	int ax;
	int ay;
	int agent_position[2] = { ay, ax };
	void init();
	void up(agent* learner);
	void down(agent* learner);
	void right(agent* learner);
	void left(agent* learner);
};

void agent::init() {
	ax = 1;
	ay = 1;
	agent_position[1] = ax;
	agent_position[0] = ay;

} 

void agent::up(agent* plearner) {
	ay = plearner->ay - 1;   											 // agent's y position is moved up 1
	agent_position[0] = ay;
};

void agent::down(agent* plearner) {
	ay = plearner->ay + 1;   											 // agent's y position is moved down 1
	agent_position[0] = ay;
}


void agent::right(agent* plearner) {
	ax = plearner->ax + 1;   											 // agent's x position is moved right 1
	agent_position[1] = ax;
}

void agent::left(agent* plearner) {
	ax = plearner->ax - 1;   											 // agent's x position is moved left 1
	agent_position[1] = ax;
}

/////////////////////////////////////////////////
///////////////// DOMAIN STUFF //////////////////
/////////////////////////////////////////////////

class domain {
public:
	int x;
	int y;
	void init();
	void write();
	void show(agent* plearner);
	void position(domain* pgrid, agent* plearner);
	vector<vector<int>> matrix;
};

void domain::init() {
	cout << "Please choose how many rows \n x = " << endl;
	cin >> x;
	cout << "Please choose how many columns \n y = " << endl;
	cin >> y;
	matrix.resize(x);
	for (int i = 0; i < x; i++) {
		matrix[i].resize(y);
	}
	for (int t = 0; t < x; t++) {
		for (int j = 0; j < y; j++) {
			matrix[t][j] = 1;
		}
	}
	cout << endl;

}

// obtained from http://stackoverflow.com/questions/1403150/how-do-you-dynamically-allocate-a-matrix

void domain::write() {
	for (int t = 0; t < x; t++) {
		for (int j = 0; j < y; j++) {
			matrix[t][j] = 1;
		}
	}
	cout << endl;
}

void domain::show(agent* plearner) {
	for (int o = 0; o < x; o++) {
		for (int p = 0; p < y; p++) {
			cout << matrix[o][p] << " ";																									// show matrix
		}
		cout << endl;
	}
	cout << "Your x coordinate is " << plearner->ax+1 << " and your Y coordinate is " << plearner->ay+1 << "\n" << endl;
}

void domain::position(domain* pgrid, agent* plearner) {
	int a = plearner->agent_position[0];
	int b = plearner->agent_position[1];
	int AP = 9;
	string position = "A";
	pgrid->matrix[a][b] = AP;
}



/////////////////////////////////////////////////
///////////////// BUMP THINGS ///////////////////
/////////////////////////////////////////////////



void bumper() {
	// use an if statement to see if the agent's xy coordinate is greater than the x/ymax of the domain
	// for extreme cases, find the difference between the agent's coordinates and max coordinates of the domain
}



/////////////////////////////////////////////////
///////// MOVING AGENT BACK TO BOARD FROM ///////
///////// EXTREEEEEEEEEEEME COORDINATES /////////
/////////////////////////////////////////////////

void testA(agent* plearner, domain* ax, domain* ay) {
	// set the agent's x and y coordinates to a large value
	// use the bumper max function
	plearner->ax = 10000;
	plearner->ay = 10000;


}

/////////////////////////////////////////////////
//////// HUMAN CONTROLLED NAVIGATION ////////////
/////////////////////////////////////////////////

void testB() {
	// lots of cin ?????
}



/////////////////////////////////////////////////
///////////// HARD CODED NAVIGATION /////////////
/////////////////////////////////////////////////

void testC() {
	// if agent x > goal x, agent x - 1
	// if agent y > goal y, agent y - 1
	// if agent x < goal x, agent x + 1
	// if agent y < goal y, agent y + 1
}

int main()
{
	srand(time(NULL));
	cout << "Coordinates start from 1,1 at top left corner. " << endl;
	agent learner;
	learner.init();
	agent* plearner = &learner;
	domain grid;
	grid.init();
	domain* pgrid = &grid;
	//
	grid.position(pgrid, plearner);
	grid.show(plearner);
	//
	plearner->up(plearner);
	grid.write();
	grid.position(pgrid, plearner);
	grid.show(plearner);
	//
	plearner->right(plearner);
	grid.write();
	grid.position(pgrid, plearner);
	grid.show(plearner);
	//
	plearner->down(plearner);
	grid.write();
	grid.position(pgrid, plearner);
	grid.show(plearner);
	//
	plearner->left(plearner);
	grid.write();
	grid.position(pgrid, plearner);
	grid.show(plearner);
	//

	// if statement to check if the goal's coordinates match the agent's coordinates
	// if (agent x position != goal x position && agent y position != goal)
	//    cout << agent position << endl;
	//    cout << goal position << endl;
	//  cout << Press W, A, S, or D for Up, Left, Down, or Right movement
	//    input = cin >>
	//   	 if
	return 0;
}