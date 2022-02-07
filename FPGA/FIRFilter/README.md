This file describes the implemented design of this project.
An FIR filter is implemented in Vivado and described with VHDL. 
A 802.11b file is taken and information is extracted using MATLAB/Octave and a data input file is generated.
This includes a Real and Imaginary Signal. These signals are then passed to the FPGA design in vivado and the output stored to another file.
The same data input file that was generated is also used as the input for another MATLAB/Octave script that performs similar filtering operations.
The results of the two operations are compared as well as their values in the logarithmic scale.
These results are all displayed on graphs to be compared. Instructions on how to run the project are in the file called 'ReadMe.txt'
