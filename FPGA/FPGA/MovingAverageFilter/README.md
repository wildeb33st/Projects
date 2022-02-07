This is to describe the Project 'Moving Average Filter' which was implemented in a Vivado using VHDL.

The following describes the design parameters:

Implement a running average low pass filter with Vivado and VHDL.
The width of the filter window must be have a bit width of eight and while the inputs must be 16-bit wide.

The testbench has to generate free running 4-bit counter at the filter imput (increment on each clock cycle). The filter result delay is 1 clock cycle (i.e. given current sample and 7 previous samples their average appears at the output on the next clock cycle).
Perform averaging by truncation at the output while full precision is kept inside running sum block.
Reset signal is not to be applied, therefore the accumulator (res) and delay lines' signals are initialized with zeros when declared.

This project makes use of MATLAB/Octave to generate results and compare to those of the FPGA as a form of reporting.

In the subfolder 'Project' under the 'MovingAverageFilter' parent folder, there are instructions for running the project yourself and seeing outputs.
If you would like to implement it yourself, it is advised to only copy that specific folder as the rest as only uploaded in the interest of completeness.
