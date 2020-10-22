# Concurrent Traffic Simulation

<img src="data/traffic_simulation.gif"/>

This is a Concurrency project for C++. 

Each intersection has been equipped with a traffic light. In this project, I built a suitable and thread-safe communication protocol between vehicles and intersections to complete the simulation. 

## Dependencies for Running Locally
* cmake >= 2.8
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* OpenCV >= 4.1
  * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./traffic_simulation`.

## Project Tasks

When the project was built initially, all traffic lights were green. Now, the traffic simulation runs with red lights controlling traffic, just as in the .gif file above.

## Debugging with VSCode

In addition I list below the steps used to debug this project using VS Code and [here](https://youtu.be/pThGzmT0C7E) is a video showing the steps.
1.	Create a .vscode directory in your project directory
2.	Copy the launch.json file (you see in the video) inside the .vscode directory
3.	Make sure you have the Makefile file in your project directory
4.	Run the commands

    4.1. "make clean" and "make debug"

5. The first command will cleanup unnecessary files and second command will generate your monitor project in debug mode
6. Open VS code inside the project directory
7. Set a breakpoint in a cpp file you want to stop
8. Click Debug > Start debugging
9. The program will stop in the first breakpoint

And voila, happy debugging!