wr_sig_full = round(sig_full);    % Original file scaling to write it to text file
dlmwrite('data2fpga2.dat',(wr_sig_full));

imag_sig = round(sig_imag);
dlmwrite('data2fpga_imag.dat',(imag_sig));

