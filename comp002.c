#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "graphics.h"

// for View 
const int width = 800;
const int height = 600;
const int sideLength = 40;
const int top_grid =50;
const int left_grid =50;

//grid constants
const int MIN_X = 0;
const int MIN_Y = 0;
const int MAX_X = 9;
const int MAX_Y = 9;

//Directions CONSTANT
const int DIR_UP  = 12;
const int DIR_RIGHT  = 3;
const int DIR_DOWN  = 6;
const int DIR_LEFT  = 9;


// Global destination
int vertical_dest,horizontal_dest;

// if obstacle
bool at_bloc = false;

// robot properties
int x,y,dir;

// trying to move forward
int try_x,try_y;

int initialX;
int initialY;
int initialDirection;
int markerX;
int markerY;
// blocs (obstacles)
const int nbBlocs = 4;
int blocs[4][2];

// View
// draw 10 x 10 grid
void drawGrid()
{
      int i = 0;
      int j = 0;
      for(i=0; i < 10; i += 1)
      {
          for(j=0; j<10; j += 1)
          {
              drawRect(i*sideLength + left_grid, j*sideLength + top_grid, sideLength, sideLength);
          }
          printf("\n");
      }
       return;

}

// draw obstacle in the grid
void drawObstacle(int i, int j)
{
    setColour(red);
    fillRect(i*sideLength + left_grid, j*sideLength + top_grid, sideLength, sideLength);
    return;
}

//draw empty rect to replace the old one when moving
void drawNewRect(int i, int j)
{
    setColour(white);
    fillRect(i*sideLength + left_grid, j*sideLength + top_grid, sideLength, sideLength);
    setColour(black);
    drawRect(i*sideLength + left_grid, j*sideLength + top_grid, sideLength, sideLength);
    return;
}

//draw robot
void drawRobot(int i, int j, int dir)
{
    setColour(green);
    // robot facing the right
    if(dir == 3)
    {
        int xCoords[] = {(i*sideLength)+left_grid, (i*sideLength)+left_grid, (i*sideLength)+ sideLength+ left_grid};
        int yCoords[] = {j*sideLength +top_grid, j*sideLength +sideLength +top_grid, (j*sideLength)+20 +top_grid};
        fillPolygon(3, xCoords, yCoords);
    }
    //robot facing down
    if(dir == 6)
    {
        int xCoords[] = {(i*sideLength)+left_grid, (i*sideLength)+sideLength+left_grid, (i*sideLength)+ 20+ left_grid};
        int yCoords[] = {j*sideLength +top_grid, j*sideLength +top_grid, (j*sideLength)+sideLength +top_grid};
        fillPolygon(3, xCoords, yCoords);
    }
    //robot facing left
    if(dir == 9)
    {
        int xCoords[] = {(i*sideLength)+ sideLength+left_grid, (i*sideLength)+sideLength+left_grid, (i*sideLength)+ left_grid};
        int yCoords[] = {j*sideLength +top_grid, j*sideLength + sideLength +top_grid, (j*sideLength)+20 +top_grid};
        fillPolygon(3, xCoords, yCoords);
    }
    // robot facing up
    if(dir == 12)
    {
         int xCoords[] = {(i*sideLength)+left_grid, (i*sideLength)+sideLength+left_grid, (i*sideLength)+ 20+ left_grid};
         int yCoords[] = {j*sideLength + sideLength+top_grid, j*sideLength +sideLength+top_grid, (j*sideLength) +top_grid};
         fillPolygon(3, xCoords, yCoords); 
    }
    
}

// draw marker
void drawMarker(int i , int j){
    setColour(gray);
    fillRect(i*sideLength + left_grid, j*sideLength + top_grid, sideLength, sideLength);
}

// initialise the view
void initView(){
	// draw Grid
    setWindowSize(width, height);
    drawGrid();
	// draw marker 
	drawMarker(markerX, markerY);

	// draw blocs
	for (int j=0; j<nbBlocs;j++){
	    drawObstacle(blocs[j][0] , blocs[j][1]);
	}
	// draw robot
    drawRobot(initialX, initialY, initialDirection);

}

void cleanView(){
    drawNewRect(x,y);
}

// after moving
void updateView(){
    drawRobot(x,y,dir);
    sleep(500);
}

// Model (initialising obstacles/blocs)
void initBlocs(){
    // bloc 1
    blocs[0][0] = 6;
    blocs[0][1] = 3;
    // bloc 2
    blocs[1][0] = 9;
    blocs[1][1] = 3;
    // bloc 3
    blocs[2][0] = 2;
    blocs[2][1] = 5;
    // bloc 4
    blocs[3][0] = 4;
    blocs[3][1] = 9;
}


// turn clockwise
void right() 
{
	if (dir == DIR_RIGHT) 
    {
		dir = DIR_DOWN;		 
	    return;
    }
	if (dir == DIR_DOWN) 
    {
		dir = DIR_LEFT;
	    return;
    }
	if (dir == DIR_LEFT)
    {
		dir = DIR_UP;
	    return;
	}
	if (dir == DIR_UP) 
    {
		dir = DIR_RIGHT;
	    return;
    }
}

// turn anti-clockwise
void left() 
{
	if (dir == DIR_RIGHT) 
    {
		dir = DIR_UP;		 
	    return;
    }
	if (dir == DIR_DOWN) 
    {
		dir = DIR_RIGHT;
	    return;
    }
	if (dir == DIR_LEFT)
    {
		dir = DIR_DOWN;
	    return;
	}
	if (dir == DIR_UP) 
    {
		dir = DIR_LEFT;
	    return;
    }
}

// switch directions
void reverseHorizontalDest()
{
	if (horizontal_dest == DIR_RIGHT) 
    { 
		horizontal_dest = DIR_LEFT;
    }
	else
    {
		horizontal_dest = DIR_RIGHT;
	}
}

bool reverseVerticalDest()  
{
    if (vertical_dest == DIR_DOWN)
    {  
		if (((dir == DIR_RIGHT) && (x == MAX_X) && (y == MAX_Y)) || ((dir == DIR_LEFT) && (x == MIN_X) && (y == MAX_Y)) )
        { 
			vertical_dest = DIR_UP;
            return true;
		}
    }
	else
    {
		if (((dir == DIR_RIGHT) && (x == MAX_X) && (y == MIN_Y)) ||  ((dir == DIR_LEFT) && (x == MIN_X) && (y == MIN_Y)) )
        { 
			vertical_dest = DIR_DOWN;
			return true;
		}
	}
	return false;
}

void tryForward()
{
	if (dir == DIR_UP)
    {
		try_x = x;
		try_y =  y -1;
	}
	if (dir == DIR_DOWN)
    {
		try_x = x;
		try_y =  y +1;
	}
	if (dir == DIR_RIGHT)
    {
		try_x = x + 1;
		try_y =  y;
	}
	if (dir == DIR_LEFT)
    {
		try_x = x - 1;
		try_y =  y;
	}
}

// see if robot can move forward
bool canMoveForward()
{
	tryForward();

	if (try_x < MIN_X || try_x > MAX_X || try_y < MIN_Y || try_y > MAX_Y)
	{
		at_bloc = false;
		return false;
	}
	
    for (int j=0; j<nbBlocs;j++){
        if ((try_x == blocs[j][0])  && (try_y == blocs[j][1])) {
			at_bloc = true;
			return false;
		}
    }

	at_bloc = false;
	return true;
}

//move robot
void forward(){
	cleanView();
	tryForward();
	x = try_x;
	y = try_y;
	updateView();
}

void turn(char sense){
	if (sense == 'X'){
		return;
	}
	if (sense == 'R'){
		right();
	}
	else{
		left();
	}
}

// check if robot reached marker
bool isMarkerFound()
{
	if ((x == markerX) && (y == markerY))
	{ 
		return true;
	}
	return false;
}

// steps to turn when met when border or bloc
void execSteps(char* steps){
    char step;

	for (int i=0; i < strlen(steps); i++){
        step = steps[i];
		turn(step);

		if (canMoveForward()){
			forward();
			if (isMarkerFound()){
				return;
			}
		}else{
			if ((dir == DIR_RIGHT) || (dir == DIR_LEFT))
			{
				// border need to make 180 turn
				right();
				right();
			}
			return;
		}
    }

}

void atBorder(){
	char* steps;

	if 
	(
		((vertical_dest == DIR_DOWN) && (dir == DIR_RIGHT)) 
		|| 
		((vertical_dest == DIR_UP) && (dir == DIR_LEFT))
	)
	{ 
	    steps =  "RR";
    }
	else
    {
	    steps = "LL";
	}

	printf("START AT BORDER"); 
	printf("\n");

	execSteps(steps);

	printf("FINISH AT BORDER"); 
	printf("\n");

	reverseHorizontalDest();
}

void arroundBloc()
{
	char* steps = "RLXLR";

	if (dir == DIR_RIGHT || dir == DIR_LEFT) 
    {
		if 
		(
			(vertical_dest == DIR_DOWN && horizontal_dest == DIR_RIGHT ) 
			|| 
			(vertical_dest == DIR_UP && horizontal_dest == DIR_LEFT)
		) 
		{ 
			steps = "RLXLR";
        }
		else
        {
			steps = "LRXRL";
		}

		// at MAX_Y or MIN_Y (outside grid)
		if 
		(
			(y == MAX_Y  && horizontal_dest == DIR_RIGHT) 
			|| 
			(y == MIN_Y  && horizontal_dest == DIR_LEFT)
		)
		{ 
			steps = "LRXRL";
		}

		if 
		(
			(y == MAX_Y  && horizontal_dest == DIR_LEFT) 
			|| 
			(y == MIN_Y  && horizontal_dest == DIR_RIGHT)
		)
		{ 
			steps = "RLXLR";
		}
    }
	else  // Down Or UP
    {
		if 
		(
			(dir == DIR_DOWN && horizontal_dest == DIR_RIGHT) 
			|| 
			(dir == DIR_UP && horizontal_dest == DIR_LEFT)
		) 
		{ 
			steps  = "RLR";
        }
		else
        {
			steps = "LRL";
		}
		reverseHorizontalDest();
	}

	printf("start arround bloc");
	printf("\n");

	execSteps(steps);

	printf("finish arround bloc");
	printf("\n");
}

void start(){
	bool scaning_all;
	int i = 0;

	vertical_dest = DIR_DOWN; // stategie of global destination
	horizontal_dest = initialDirection;
	scaning_all = false;
	at_bloc = false;

	x = initialX;
	y = initialY;
	dir = initialDirection;

	while (true)
    {
		if (canMoveForward())
        { 
			if (isMarkerFound())
			{
				return;
			}

			forward();

			// if zigzag of half plan is over
			if (reverseVerticalDest())
            {
				if(!scaning_all)  
                {
					scaning_all = true;
                } 
				else
                {
					printf("Marker not found");
					return;
				}
			}
			i++;
        }
		else
        {
			if (at_bloc)
            { 
				arroundBloc();
            } 
			else // border
            {
				atBorder();
			}
		}
		
	}
}

// main function
// referenced from coursework pdf and week5 videos
int main(int argc, char** argv){	
    for (int i=1; i <= argc; i++){
        if (i==1){
            initialX = atoi(argv[i]);
        }
        if (i==2){
            initialY = atoi(argv[i]);
        }
        if (i==3){
            initialDirection = atoi(argv[i]);
        }
        if (i==4){
            markerX = atoi(argv[i]);
        }
        if (i==5){
            markerY = atoi(argv[i]);
        }

    }

	initBlocs();
	initView();
	start();

}
