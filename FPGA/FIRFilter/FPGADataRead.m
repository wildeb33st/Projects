%% Read FPGA simulation results from file
fpga_result = dlmread('data_from_fpga.dat');
%fpga_result = 20*log(fpga_result); % FPGA results reverse scaling for correct comparing with Matlab results

%This is for the Imaginary component of the signal
fpga_resultIm = dlmread('data_from_fpga_Im.dat');
