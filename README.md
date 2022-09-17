# C-grid-robot
zigzag scheme moving robot
When run, the program should show a 10x10 grid with 4 red obstacles (adjustable number and positions), a gray marker (adjustable position), and a robot (green triangle with adjustable position). The robot keeps moving forward and we have 4 different possibilities:
• The robot is met by a grid border: in this case, in the first half of the program (before robot reaches bottom of the grid) the robot must move one step down and continue moving forward in the opposite direction. After reaching the bottom of the grid, it starts moving upward toward the top of the grid.
• The robot is met by an obstacle and therefore has to execute a series of steps to find a way around It (for example turn left move forward turn left again and start moving
forward in a U or ∩ shape.
• The robot hits the bottom of the grid, therefore it starts moving in the opposite
direction, towards the top of the grid. • The robot finds the marker and stops.
We can see that the robot moves around the grid in zigzags, and this is to cover all lines and find the marker even if we change the positions of the obstacles and marker. There are other situations that can be the result of a combination of the previous ones, for example the robot is met by both a border and an obstacle. These were treated separately.
The directions were considered as a clock abstraction to omit chars from the function and keep ints only, 3 is in reference to east, 9 to west, 12 to north and 6 to south.
To change the number or position of obstacles, the function initBloc() and nbbloc must be modified.
After compiling, enter the coordinates of the robot (x position, y position, direction) and the coordinates of the marker (x position, y position) right after ./a.out
The positions are defined from the square’s position in the grid, the squares are counted horizontally and vertically from 0 to 9. For example, square 2, 3 is in the third column fourth row. Positions use the clock system mentioned above so only 3, 6, 9, 12 could be entered.
The command used to compile the code is:
gcc comp002.c graphics.c
The command used to run after compiling is (example robot if facing east in square 3,3 and marker is in square 3,2):
./a.out 3 3 3 3 2 | java -jar drawapp-2.0.jar
