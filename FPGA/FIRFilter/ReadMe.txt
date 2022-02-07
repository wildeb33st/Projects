Below are the instructions running the Lab. These instructions were written 
for and operating system running Linux but will also work for a system running
Windows as well. 

1) Navigate to the 'sources' directory and modify the parameters for the 
   writeLn, writeLnIm, readLn, readLnIm to the file path to the directory
   the folder is in. Note, that you should not change the filename at the end
   of the path, only the path itself.

2) Open octave/MATLAB and run the script WifiRead. This will generate two files
'data2fpga2.dat' and 'data2fpga_imag.dat'. These will be used by the filter to 
generate the outputs. If you are using octave, you will need to install the signal processing package and load it with the command 'pkg load signal' prior to running WifiRead.

3) Start vivado in TCL mode after navigating to the folder where the project
is located. Vivado will run the synthesis and implementation and generate two
new files, 'data_from_fpga.dat' and 'data_from_fpga_Im.dat'. At this point the
FPGA completed the filtering process.

4) Return to MATLAB/Octave and run the command Comp. This will generate two
figures for the real and imaginary components and compare them to the
filtering process that MATLAB/octave has applied. 

At this point the Lab is complete.
