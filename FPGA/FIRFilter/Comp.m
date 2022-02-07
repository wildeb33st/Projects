%Read the data from the .pcm file
%Note that for octave the signal package must be loaded (pkg load signal)
WifiRead

%Stating the Cyclic Prefix being used; in this case the 13-chip Barker sequence
CP = [1 1 1 1 1 -1 -1 1 1 -1 1 -1 1];

%flipping the Barker sequence as this is a matched filter
s = flip(CP);

%SOP is the convolution of the Barker sequence and the data
SOP = conv(s, data_i);

%Reading the results of the FIR filter from the FPGA
FPGADataRead;
figure (1);
%plotting FPGA Results
subplot(4,1,1)
plot(fpga_result)
title('Real Component FPGA Results')
axis([0 20000 -250 100])

%plotting the results from MATLAB/Octave
subplot(4,1,2)
plot(SOP)
title('Real Component MATLAB Results')
axis([0 20000 -250 100])

%Power in the signal; abs needs to be used as the result is complex due to 
% negative numbers
SOP_dB = abs(20*log(SOP));
subplot(4,1,3)
plot(SOP_dB)
title('Real Component SOP_dB MATLAB')
axis([0 20000 -30 80])

%plotting the power of the results from the FPGA design
FOP_dB = abs(20*log(fpga_result));
subplot(4,1,4)
plot(FOP_dB)
title('Real Component FOP_dB MATLAB')
axis([0 20000 -30 80])


%Below here is for the imaginay component
figure (2);

%Stating the Cyclic Prefix being used; in this case the 13-chip Barker sequence
%CP inverted since this is the imaginary component
CPIm = [-1 -1 -1 -1 -1 1 1 -1 -1 1 -1 1 -1];

%flipping the Barker sequence as this is a matched filter
sIm = flip(CPIm);

%SOP is the convolution of the Barker sequence and the data
SOPIm = conv(sIm, data_q);

%plotting FPGA Results
subplot(4,1,1)
plot(fpga_resultIm)
title('Imaginary Component FPGA Results')
axis([0 20000 -150 200])

%plotting the results from MATLAB/Octave
subplot(4,1,2)
plot(SOPIm)
title('Imaginary Component MATLAB Results')
axis([0 20000 -150 200])

%Power in the signal; abs needs to be used as the result is complex due to
% negative numbers
SOP_dBIm = abs(20*log(SOPIm));
subplot(4,1,3)
plot(SOP_dBIm)
title('Imaginary Component SOP_dB MATLAB')
axis([0 20000 -30 80])

%plotting the power of the results from the FPGA design
FOP_dBIm = abs(20*log(fpga_resultIm));
subplot(4,1,4)
plot(FOP_dBIm)
title('Imaginary Component FOP_dB MATLAB')
axis([0 20000 -30 80])
