# Graphing-Calculator
## Introduction
This C program is developed for understanding the general shape of explicit mathematical functions under a coordinate system.
## Members
* Aakash Adhikari
* Abhishek Kumar Kayastha
* Aniket Nayak
* Ankit Bhandari
## Project Description
Our project for ease of development is divided into many program files. It is done to reduce complexity of the complete program.Our project is just a simple
way to visualize the shape of any mathematical [function](https://en.wikipedia.org/wiki/Function_(mathematics)) expressed in [Cartesian-Coordinate-System](https://en.wikipedia.org/wiki/Cartesian_coordinate_system). We have managed to 
achieve this using very few functions and header files thus reducing the size of our project.
## Running the program
Running the program is as straight forward as executing the "Graphing-Calculator.exe" file. Compiling the .c files is also straight-forward , exepect for "prototype.c".
Due to the use of WINAPI the "-mwindows" needs to be added at the end
```console
gcc prototype.c -o prototype.exe -mwindows
```
## Notes
* This program is only able to graph explicit functions ( y=f(x) ).
* The graph may look thinner in some region due to increase in rate of change of the function, this problem can be mitigated by changing the tolerance.
* The function must be written according to the c syntax (Eg: arcsin(x) becomes asin(x), e<sup>x</sup> becomes exp(x) and so on).
* Be extra careful not to forget brackets. The program will not work if even one is missing or misplaced.
* The current scale of the graph is the centimeter scale and can be changed from the program file.
