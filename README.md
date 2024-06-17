# Electromagnetic-Fields
The Iteration Method to determine the Electric Field when it's varying in two different directions
The Problem:
The problem is the potential is completely specified on the boundaries of a given region and the potential doesn’t vary in only one direction and to solve this problem we need to use THE IRERATION METHOD which can take a lot of time if used with a pencil and paper, so it’s preferable to use digital computers.
The Algorithm:
  •	Initialize the grid with initial voltage values for conductors and gaps.
  •	Set the central point voltage value to the average voltage of the surrounding     
    conductors and gap.
  •	Set all other grid point voltage values to -1.
  •	Iterate over the diagonal points in the grid:
    *	For each point, check if all surrounding points have valid voltage values.
    *	If so, set the voltage value of the point and it’s symmetric one to the average   
    voltage of the surrounding points.
  •	Iterate over the points of the grid:
    *	For each point, calculate the average voltage value of the surrounding points.
    *	If the difference between the calculated value and the current voltage value is less      than a 0.01, mark the accuracy is acceptable.
  •	Repeat the last step until the voltage values at all points approximately remain   
    constant and display every iteration values.
Obstacles I faced:
  •	When I started typing my code, I found that it’s getting untidy, hard to trace and   
    debug, Here I found the necessity to divide it into smaller parts using functions so   
    that I can easily debug and trace.
  •	After that I faced another problem while trying to display the grid because of using 
    C++, and after searching I came up with a solution using setw() , setprecision(), and 
    setfill() functions from iomanip library.
