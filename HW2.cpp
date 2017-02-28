// HW2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include <array>
#include <string.h>
#include <string>
#include <sstream>

using namespace std;



/////////////////////////////////////////////////
/////////////// AGENT STUFF /////////////////////
/////////////////////////////////////////////////



class agent {
public:
	int ax;
	int ay;
	int agent_position[2] = { ay, ax };																								// 2 entry array
	void init();
};

void agent::init() {
	ax = 0;																															// places learner at (0,0)
	ay = 0;
	agent_position[1] = ax;																											// stores agent's x coord in 2nd data entry
	agent_position[0] = ay;																											// stores agent's y coord in 1st data entry
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
	void goal(domain* pgrid);
	int goal_x;
	int goal_y;
	vector<vector<int>> matrix;																										// 2D vector
};

void domain::init() {
	cout << "Please choose how many rows \n x = " << endl;
	cin >> x;   																													// user input for rows
	cout << "Please choose how many columns \n y = " << endl;
	cin >> y;   																													// user input for columns
	matrix.resize(x);																										  		// creates x columns (i think)
	for (int i = 0; i < x; i++) {
		matrix[i].resize(y);																										// creates y rows (i think)
	}
	for (int t = 0; t < x; t++) {
		for (int j = 0; j < y; j++) {
			matrix[t][j] = 1;																										// fills board with 1's
		}
	}
	cout << endl;
	goal_x = rand() % x;																											// goal placed at a random X coordinate
	goal_y = rand() % y;																											// goal placed at a random Y coordinate
}
// obtained from http://stackoverflow.com/questions/1403150/how-do-you-dynamically-allocate-a-matrix



void domain::write() {
	for (int t = 0; t < x; t++) {
		for (int j = 0; j < y; j++) {
			matrix[t][j] = 1;   																									// populates board with 1's
		}
	}
	cout << endl;
}

void domain::show(agent* plearner) {
	for (int o = 0; o < x; o++) {
		for (int p = 0; p < y; p++) {
			cout << matrix[o][p] << "   ";   																						// show matrix
		}
		cout << endl;
	}
	cout << "\nYour X coordinate is " << plearner->ax << " and your Y coordinate is " << plearner->ay << ".\n" << endl;   			// display learner coordinates
	cout << "The goal's coordinates are at " << goal_y << "," << goal_x << ".\n" << endl;											// display goal coordinates
}

void domain::position(domain* pgrid, agent* plearner) {   																			// show where the agent is on grid
	int a = plearner->agent_position[0];
	int b = plearner->agent_position[1];
	int AP = 9;																														// agent represented as a 9 on the board
	pgrid->matrix[a][b] = AP;																										// places agent representation on board
}

void domain::goal(domain* pgrid) {   																								// show where goal is on grid
	int goal = 5;
	pgrid->matrix[goal_y][goal_x] = goal;																							// places goal coords onto gridworld
}



/////////////////////////////////////////////////
/////////////// MOVEMENT FUNCTIONS //////////////
/////////////////////////////////////////////////



void up(agent* plearner) {
	plearner->ay = plearner->ay - 1;  																								// agent's y position is moved up 1
	plearner->agent_position[0] = plearner->ay;
};

void down(agent* plearner) {
	plearner->ay = plearner->ay + 1;  																								// agent's y position is moved down 1
	plearner->agent_position[0] = plearner->ay;
}


void right(agent* plearner) {
	plearner->ax = plearner->ax + 1;  																								// agent's x position is moved right 1
	plearner->agent_position[1] = plearner->ax;
}

void left(agent* plearner) {
	plearner->ax = plearner->ax - 1;  																								// agent's x position is moved left 1
	plearner->agent_position[1] = plearner->ax;
}



/////////////////////////////////////////////////
///////////////// BUMP THINGS ///////////////////
/////////////////////////////////////////////////



void bumper_down(agent* plearner, domain* pgrid, int user_input) {   																// (-,0) & input = up
	if (plearner->ay == 0 && user_input == 1) {
		plearner->ay = plearner->ay + 1;
		plearner->agent_position[0] = plearner->ay;
		cout << "bumped down" << endl;
	}
}

void bumper_up(agent* plearner, domain* pgrid, int user_input) {   																	// (-,y) & input = down
	if (plearner->ay == pgrid->y - 1 && user_input == 2) {
		plearner->ay = plearner->ay - 1;
		plearner->agent_position[0] = plearner->ay;
		cout << "bumped up\n" << endl;
	}
}

void bumper_left(agent* plearner, domain* pgrid, int user_input) {   																// (x,-) & input = right
	if (plearner->ax == pgrid->x - 1 && user_input == 3) {
		plearner->ax = plearner->ax - 1;
		plearner->agent_position[1] = plearner->ax;
		cout << "bumped left\n" << endl;
	}
}

void bumper_right(agent* plearner, domain* pgrid, int user_input) {   																// (0,-) & input = left
	if (plearner->ax == 0 && user_input == 4) {
		plearner->ax = plearner->ax + 1;
		plearner->agent_position[1] = plearner->ax;
		cout << "bumped right\n" << endl;
	}
}

// corner cases where agent can go out of bounds by going in two directions

void bumper_top_left(agent* plearner, domain* pgrid, int user_input) {
	if (plearner->ax == 0 && plearner->ay == 0 && user_input == 4) {   																// (0,0) & input = left
		plearner->ax = plearner->ax + 1;
		plearner->agent_position[1] = plearner->ax;
		cout << "bumped right\n" << endl;
	}
	if (plearner->ax == 0 && plearner->ay == 0 && user_input == 1) {   																// (0,0) & input = up
		plearner->ay = plearner->ay + 1;
		plearner->agent_position[0] = plearner->ay;
		cout << "bumped down\n" << endl;
	}
}

void bumper_top_right(agent* plearner, domain* pgrid, int user_input) {
	if (plearner->ax == pgrid->x - 1 && plearner->ay == 0 && user_input == 3) {   													// (x,0) & input = right
		plearner->ax = plearner->ax - 1;
		plearner->agent_position[1] = plearner->ax;
		cout << "bumped left\n" << endl;
	}
	if (plearner->ax == pgrid->x - 1 && plearner->ay == 0 && user_input == 1) {   													// (x,0) & input = up
		plearner->ay = plearner->ay + 1;
		plearner->agent_position[0] = plearner->ay;
		cout << "bumped down\n" << endl;
	}
}

void bumper_bot_left(agent* plearner, domain* pgrid, int user_input) {
	if (plearner->ax == 0 && plearner->ay == pgrid->y - 1 && user_input == 4) {   													// (0,y) & input = left
		plearner->ax = plearner->ax + 1;
		plearner->agent_position[1] = plearner->ax;
		cout << "bumped left\n" << endl;
	}
	if (plearner->ax == 0 && plearner->ay == pgrid->y - 1 && user_input == 2) {   													// (0,y) & input = down
		plearner->ay = plearner->ay - 1;
		plearner->agent_position[0] = plearner->ay;
		cout << "bumped up\n" << endl;
	}
}

void bumper_bot_right(agent* plearner, domain* pgrid, int user_input) {
	if (plearner->ax == pgrid->x - 1 && plearner->ay == pgrid->y - 1 && user_input == 3) {   										// (x,y) & input = right
		plearner->ax = plearner->ax - 1;
		plearner->agent_position[1] = plearner->ax;
		cout << "bumped left\n" << endl;
	}
	if (plearner->ax == pgrid->x - 1 && plearner->ay == pgrid->y - 1 && user_input == 2) {   										// (x,y) & input = down
		plearner->ay = plearner->ay - 1;
		plearner->agent_position[0] = plearner->ay;
		cout << "bumped up\n" << endl;
	}
}



/////////////////////////////////////////////////
///////// MOVING AGENT BACK TO BOARD FROM ///////
///////// EXTREEEEEEEEEEEME COORDINATES /////////
/////////////////////////////////////////////////



void testA(agent* plearner, domain* pgrid) {
	cout << "Enter an extreme X,Y coordinate" << endl;
	cout << "X coordinate =" << endl;
	cin >> plearner->ax;
	plearner->agent_position[1] = plearner->ax;
	cout << "Y coordinate =" << endl;
	cin >> plearner->ay;
	plearner->agent_position[0] = plearner->ay;
	cout << "\nExtreme coordinates are " << plearner->ax << "," << plearner->ay << "\n" << endl;
	if (plearner->ax > pgrid->x) {																									// reposition learner's x coord
		plearner->ax = 0;
		plearner->agent_position[1] = plearner->ax;
	}
	if (plearner->ay > pgrid->y) {																									// reposition learner's y coord
		plearner->ay = 0;
		plearner->agent_position[0] = plearner->ay;
	}
	cout << "Magic happens. \n" << endl;
	cout << "New coordinates are " << plearner->ax << "," << plearner->ay << "\n" << endl;
	pgrid->goal(pgrid);
	pgrid->position(pgrid, plearner);   																							// positions the learner
	pgrid->write();
	pgrid->position(pgrid, plearner);
	pgrid->show(plearner);
}



/////////////////////////////////////////////////
//////// HUMAN CONTROLLED NAVIGATION ////////////
/////////////////////////////////////////////////



void testB(agent* plearner, domain*pgrid) {
	cout << "Coordinates start from 1,1 at top left corner. \nThe AGENT is represented by a 9. \nThe GOAL is represented by a 5. \nAn empty space is represented by a 1. \n" << endl;
	pgrid->show(plearner);
	int check = 1;
	while (check < 50) {
		int user_input;
		cout << "check = " << check << endl;
		cout << "Move the agent (9) around. 1 to move up, 2 to move down, 3 to move right, 4 to move left!\n" << endl;
		cin >> user_input;
		if (user_input == 1) {																										// up
			bumper_down(plearner, pgrid, user_input);
			bumper_top_left(plearner, pgrid, user_input);
			bumper_top_right(plearner, pgrid, user_input);
			up(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
		}
		if (user_input == 2) {																										// down
			bumper_up(plearner, pgrid, user_input);
			bumper_bot_left(plearner, pgrid, user_input);
			bumper_bot_right(plearner, pgrid, user_input);
			down(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
		}
		if (user_input == 3) {																										// right
			bumper_left(plearner, pgrid, user_input);
			bumper_top_right(plearner, pgrid, user_input);
			bumper_bot_right(plearner, pgrid, user_input);
			right(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
		}
		if (user_input == 4) {																										// left
			bumper_right(plearner, pgrid, user_input);
			bumper_top_left(plearner, pgrid, user_input);
			bumper_bot_left(plearner, pgrid, user_input);
			left(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
		}
		if (plearner->ax == pgrid->goal_x && plearner->ay == pgrid->goal_y) {														// ends the while loop
			check = 100;
			cout << "Goal reached! Program ending.\n" << endl;
		}

	}

}



/////////////////////////////////////////////////
///////////// HARD CODED NAVIGATION /////////////
/////////////////////////////////////////////////



void testC(agent* plearner, domain* pgrid) {
	// if agent x > goal x, agent x - 1 (LEFT)
	// if agent y > goal y, agent y - 1 (UP)
	// if agent x < goal x, agent x + 1 (RIGHT)
	// if agent y < goal y, agent y + 1 (DOWN)
	cout << "Coordinates start from 1,1 at top left corner. \nThe AGENT is represented by a 9. \nThe GOAL is represented by a 5. \nAn empty space is represented by a 1. \n" << endl;
	cout << "Heuristic control!" << endl;
	int user_input = 0;
	int check = 10;
	while (check < 50) {
		if (plearner->ax > pgrid->goal_x) {   																						// move left
			user_input = 4;
			bumper_right(plearner, pgrid, user_input);																				// technically, the heuristic control should never need bumpers
			bumper_top_left(plearner, pgrid, user_input);
			bumper_bot_left(plearner, pgrid, user_input);
			left(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
			cout << "Press any number to continue movement" << endl;
			int input;
			cin >> input;
		}
		else if (plearner->ax < pgrid->goal_x) {   																					// move right
			user_input = 3;
			bumper_left(plearner, pgrid, user_input);
			bumper_top_right(plearner, pgrid, user_input);
			bumper_bot_right(plearner, pgrid, user_input);
			right(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
			cout << "Press any number to continue movement" << endl;
			int input;
			cin >> input;
		}
		else if (plearner->ay < pgrid->goal_y) {   																					// move down
			user_input = 2;
			bumper_up(plearner, pgrid, user_input);
			bumper_bot_left(plearner, pgrid, user_input);
			bumper_bot_right(plearner, pgrid, user_input);
			down(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
			cout << "Press any number to continue movement" << endl;
			int input;
			cin >> input;
		}
		else if (plearner->ay > pgrid->goal_y) {   																					// move up
			user_input = 1;
			bumper_down(plearner, pgrid, user_input);
			bumper_top_left(plearner, pgrid, user_input);
			bumper_top_right(plearner, pgrid, user_input);
			up(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
			cout << "Press any number to continue movement" << endl;
			int input;
			cin >> input;
		}
		else if (plearner->ax == pgrid->goal_x && plearner->ay == pgrid->goal_y) {													// end while loop
			check = 100;
		}
		else {
			cout << "Press any number to continue movement" << endl;																// user makes next step happen, but movement is still "autonomous"
			int input;
			cin >> input;
		}
	}
}

/////////////////////////////////////////////////

int main()
{
	srand(time(NULL));
	cout << "Coordinates start from the top left corner. \nThe AGENT is represented by a 9. \nThe GOAL is represented by a 5. \nAn empty space is represented by a 1." << endl;
	agent learner;
	learner.init();
	agent* plearner = &learner;
	domain grid;
	grid.init();
	// prevents randomized goal coordinates from being placed on the agent
	while (learner.ax == grid.goal_x && learner.ay == grid.goal_y) {
		cout << "Goal coordinates were placed on agent position, please re-enter X and Y\n" << endl;
		grid.init();
	}
	domain* pgrid = &grid;
	grid.goal(pgrid);   																											// establishes goal
	grid.position(pgrid, plearner);   																								// positions the learner
	grid.show(plearner);
	// user chooses which test to do
	int test_run;
	cout << "Select a test (1 for test A, 2 for test B, 3 for test C)" << endl;
	cin >> test_run;
	if (test_run == 1) {
		testA(plearner, pgrid);
	}
	if (test_run == 2) {
		testB(plearner, pgrid);
	}
	if (test_run == 3) {
		testC(plearner, pgrid);
	}
	cout << "You found Waldo! \n" << endl;
	return 0;
}
