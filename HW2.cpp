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
	ay = plearner->ay - 1;  											  // agent's y position is moved up 1
	agent_position[0] = ay;
};

void agent::down(agent* plearner) {
	ay = plearner->ay + 1;  											  // agent's y position is moved down 1
	agent_position[0] = ay;
}


void agent::right(agent* plearner) {
	ax = plearner->ax + 1;  											  // agent's x position is moved right 1
	agent_position[1] = ax;
}

void agent::left(agent* plearner) {
	ax = plearner->ax - 1;  											  // agent's x position is moved left 1
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
	void goal(domain* pgrid);
	int goal_x;
	int goal_y;
	vector<vector<int>> matrix;
};

void domain::init() {
	cout << "Please choose how many rows \n x = " << endl;
	cin >> x;   																															 // user input for rows
	cout << "Please choose how many columns \n y = " << endl;
	cin >> y;   																															 // user input for columns
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
			matrix[t][j] = 1;   																												 // populates board with 1's
		}
	}
	cout << endl;
}

void domain::show(agent* plearner) {
	for (int o = 0; o < x; o++) {
		for (int p = 0; p < y; p++) {
			cout << matrix[o][p] << " ";   																										 // show matrix
		}
		cout << endl;
	}
	cout << "\nYour X coordinate is " << plearner->ax + 1 << " and your Y coordinate is " << plearner->ay + 1 << ".\n" << endl;   				 // display coordinates
	cout << "The goal's coordinates are at " << y << "," << x << ".\n" << endl;
}

void domain::position(domain* pgrid, agent* plearner) {   								 // show where the agent is on grid
	int a = plearner->agent_position[0];
	int b = plearner->agent_position[1];
	int AP = 9;
	string position = "A";
	pgrid->matrix[a][b] = AP;
}

void domain::goal(domain* pgrid) {   													 // show where goal is on grid
	goal_x = x - 1;
	goal_y = y - 1;
	int goal = 5;
	pgrid->matrix[goal_x][goal_y] = goal;
}



/////////////////////////////////////////////////
///////////////// BUMP THINGS ///////////////////
/////////////////////////////////////////////////



void bumper_down(agent* plearner, domain* pgrid, int user_input) {   						 // (-,0) & input = up
	if (plearner->ay == 0 && user_input == 1) {
		cout << "i am working" << endl;
		plearner->ay = plearner->ay + 1;
		plearner->agent_position[0] = plearner->ay;
		cout << "bumped down" << endl;
	}
}

void bumper_up(agent* plearner, domain* pgrid, int user_input) {   						 // (-,y) & input = down
	if (plearner->ay == pgrid->y && user_input == 2) {
		plearner->ay = plearner->ay - 1;
		plearner->agent_position[0] = plearner->ay;
		cout << "bumped up" << endl;
	}
}

void bumper_left(agent* plearner, domain* pgrid, int user_input) {   						 // (x,-) & input = right
	if (plearner->ax == pgrid->x && user_input == 3) {
		plearner->ax = plearner->ax - 1;
		plearner->agent_position[1] = plearner->ax;
		cout << "bumped left" << endl;
	}
}

void bumper_right(agent* plearner, domain* pgrid, int user_input) {   						 // (0,-) & input = left
	if (plearner->ax == 0 && user_input == 4) {
		plearner->ax = plearner->ax + 1;
		plearner->agent_position[1] = plearner->ax;
		cout << "bumped right" << endl;
	}
}

void bumper_top_left(agent* plearner, domain* pgrid, int user_input) {
	if (plearner->ax == 0 && plearner->ay == 0 && user_input == 4) {   					 // (0,0) & input = left
		plearner->ax = plearner->ax + 1;
		plearner->agent_position[1] = plearner->ax;
		cout << "bumped right" << endl;
	}
	if (plearner->ax == 0 && plearner->ay == 0 && user_input == 1) {   					 // (0,0) & input = up
		plearner->ay = plearner->ay + 1;
		plearner->agent_position[0] = plearner->ay;
		cout << "bumped down" << endl;
	}
}

void bumper_top_right(agent* plearner, domain* pgrid, int user_input) {
	if (plearner->ax == pgrid->x && plearner->ay == 0 && user_input == 3) {   				 // (x,0) & input = right
		plearner->ax = plearner->ax - 1;
		plearner->agent_position[1] = plearner->ax;
		cout << "bumped left" << endl;
	}
	if (plearner->ax == pgrid->x && plearner->ay == 0 && user_input == 1) {   				 // (x,0) & input = up
		plearner->ay = plearner->ay + 1;
		plearner->agent_position[0] = plearner->ay;
		cout << "bumped down" << endl;
	}
}

void bumper_bot_left(agent* plearner, domain* pgrid, int user_input) {
	if (plearner->ax == 0 && plearner->ay == pgrid->y && user_input == 4) {   				 // (0,y) & input = left)
		plearner->ax = plearner->ax + 1;
		plearner->agent_position[1] = plearner->ax;
		cout << "bumped left" << endl;
	}
	if (plearner->ax == 0 && plearner->ay == pgrid->y && user_input == 2) {   				 // (0,y) & input = down
		plearner->ay = plearner->ay - 1;
		plearner->agent_position[0] = plearner->ay;
		cout << "bumped up" << endl;
	}
}

void bumper_bot_right(agent* plearner, domain* pgrid, int user_input) {
	if (plearner->ax == pgrid->x && plearner->ay == pgrid->y && user_input == 3) {   		 // (x,y) & input = right)
		plearner->ax = plearner->ax - 1;
		plearner->agent_position[1] = plearner->ax;
		cout << "bumped left" << endl;
	}
	if (plearner->ax == pgrid->x && plearner->ay == pgrid->y && user_input == 2) {   		 // (x,y) & input = down
		plearner->ay = plearner->ay - 1;
		plearner->agent_position[0] = plearner->ay;
		cout << "bumped up" << endl;
	}
}

/////////////////////////////////////////////////
///////// MOVING AGENT BACK TO BOARD FROM ///////
///////// EXTREEEEEEEEEEEME COORDINATES /////////
/////////////////////////////////////////////////

void testA(agent* plearner, domain* pgrid) {
	cout << "Enter an extreme X,Y coordinate" << endl;
	cout << "X coordinate" << endl;
	cin >> plearner->ax;
	cout << "Y coordinate" << endl;
	cin >> plearner->ay;
	cout << "\nExtreme coordinates are " << plearner->ax << "," << plearner->ay << "\n" << endl;
	plearner->ax = 0;
	plearner->ay = 0;
	cout << "Magic happens. \n" << endl;
	cout << "New coordinates are " << plearner->ax << "," << plearner->ay << "\n" << endl;
	pgrid->goal(pgrid);
	pgrid->position(pgrid, plearner);   																															 // positions the learner
	pgrid->show(plearner);
}

/////////////////////////////////////////////////
//////// HUMAN CONTROLLED NAVIGATION ////////////
/////////////////////////////////////////////////

void testB(agent* plearner, domain*pgrid) {
	cout << "Coordinates start from 1,1 at top left corner. \nThe AGENT is represented by a 9. \nThe GOAL is represented by a 5. \nAn empty space is represented by a 1. \n" << endl;
	pgrid->show(plearner);
	while (plearner->ax != pgrid->goal_x && plearner->ay != pgrid->goal_y) {
		int user_input;
		cout << "Move the agent (9) around. 1 to move up, 2 to move down, 3 to move right, 4 to move left!" << endl;
		cin >> user_input;
		if (user_input == 1) {
			bumper_down(plearner, pgrid, user_input);
			bumper_top_left(plearner, pgrid, user_input);
			bumper_top_right(plearner, pgrid, user_input);
			plearner->up(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
		}
		if (user_input == 2) {
			bumper_up(plearner, pgrid, user_input);
			bumper_bot_left(plearner, pgrid, user_input);
			bumper_bot_right(plearner, pgrid, user_input);
			plearner->down(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
		}
		if (user_input == 3) {
			bumper_left(plearner, pgrid, user_input);
			bumper_top_right(plearner, pgrid, user_input);
			bumper_bot_right(plearner, pgrid, user_input);
			plearner->right(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
		}
		if (user_input == 4) {
			bumper_right(plearner, pgrid, user_input);
			bumper_top_left(plearner, pgrid, user_input);
			bumper_bot_left(plearner, pgrid, user_input);
			plearner->left(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
		}
		if (user_input == 5) {
			cout << "bumped" << endl;
		}

	}

}



/////////////////////////////////////////////////
///////////// HARD CODED NAVIGATION /////////////
/////////////////////////////////////////////////

void testC(agent* plearner, domain* pgrid) {
	// if agent x > goal x, agent x - 1
	// if agent y > goal y, agent y - 1
	// if agent x < goal x, agent x + 1
	// if agent y < goal y, agent y + 1
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
	domain* pgrid = &grid;
	//
	grid.goal(pgrid);   																																		 // establishes goal
	cout << pgrid->goal_x << "," << pgrid->goal_y << endl;
	grid.position(pgrid, plearner);   																															 // positions the learner
	grid.show(plearner);
	cout << pgrid->goal_x << "," << pgrid->goal_y << endl;
	int test_run;
	cout << "\nSelect a test (1 for test A, 2 for test B, 3 for test C)" << endl;
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

	// visual display of the grid
	// begin user inputs
	/*while (plearner->ax != pgrid->goal_x && plearner->ay != pgrid->goal_y) {
	int user_input;
	cout << "Move around the agent (9). 1 to move up, 2 to move down, 3 to move right, 4 to move left!" << endl;
	cin >> user_input;
	if (user_input == 1) {
	cout << plearner->ax << plearner->ay << user_input << endl;
	bumper_down(plearner, pgrid, user_input);
	bumper_top_left(plearner, pgrid, user_input);
	bumper_top_right(plearner, pgrid, user_input);
	plearner->up(plearner);
	grid.write();
	grid.goal(pgrid);
	grid.position(pgrid, plearner);
	grid.show(plearner);
	}
	if (user_input == 2) {
	cout << plearner->ax << plearner->ay << user_input << endl;
	bumper_up(plearner, pgrid, user_input);
	bumper_bot_left(plearner, pgrid, user_input);
	bumper_bot_right(plearner, pgrid, user_input);
	plearner->down(plearner);
	grid.write();
	grid.goal(pgrid);
	grid.position(pgrid, plearner);
	grid.show(plearner);
	}
	if (user_input == 3) {
	cout << plearner->ax << plearner->ay << user_input << endl;
	bumper_left(plearner, pgrid, user_input);
	bumper_top_right(plearner, pgrid, user_input);
	bumper_bot_right(plearner, pgrid, user_input);
	plearner->right(plearner);
	grid.write();
	grid.goal(pgrid);
	grid.position(pgrid, plearner);
	grid.show(plearner);
	}
	if (user_input == 4) {
	cout << plearner->ax << plearner->ay << user_input << endl;
	bumper_right(plearner, pgrid, user_input);
	bumper_top_left(plearner, pgrid, user_input);
	bumper_bot_left(plearner, pgrid, user_input);
	plearner->left(plearner);
	grid.write();
	grid.goal(pgrid);
	grid.position(pgrid, plearner);
	grid.show(plearner);
	}
	}*/

	// while statement to check if the goal's coordinates match the agent's coordinates
	// if (agent x position != goal x position && agent y position != goal)
	//	cout << agent position << endl;
	//	cout << goal position << endl;
	//  cout << Press W, A, S, or D for Up, Left, Down, or Right movement
	//	input = cin >>
	//  	  if
	return 0;
}