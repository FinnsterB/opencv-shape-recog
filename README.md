# opencv-shape-recog
WoR-Robots shape recognition 

## Build instruction

This project uses CMake.

1) Do ```mkdir build``` in the root of this repo.
2) ```cd build``` to navigate to the new folder.
3) Generate build files with ```cmake ..```
4) Build the CMake project with ```make```
5) Run the executable with either a specification file as argument: ```./shapeRecogCMake ../specs```
6) Or run the executable with no arguments for interactive mode.

## Usage instruction
### Batch mode
In batch mode the program will try to find all shapes that correspond with the given specs. 
These specs are given in a file that's passed as a command line argument. 

### Interactive mode
Interactive mode takes no argument, but expects you to input the specs into the command line
followed by \[ENTER\]. The program will start looking for all given specifications. The program
will quit when you input "exit".

### Color calibration
If you press "C" while having an openCV window in focus, the color calibration sliders will appear.
Ideally this is not used, as it is very clumsy and I made a nice cardboard box with lights and the 
camera in it that should give the same lighting everytime. (Fingers Crossed ;)