--This represents only a single FIR filter and as such only accounts for either the real or imaginary part of the input signal` 
Library IEEE;  
 USE IEEE.Std_logic_1164.all;   
 USE IEEE.Std_logic_signed.all;     
use work.coeff_pkg.all; 
 --VHDL code for FIR filter
 
 --------------------------------------------------------------------------------------------------------
 -- Below is setting up the inputs and outputs for a single filter. Generic sets up most of the sizes
 --to be used in the design
 --------------------------------------------------------------------------------------------------------   
 entity FIR_RI is 
 
 generic (  
--           input_width :integer:=16;-- this is based on the input data width 
--           output_width:integer:=32;-- this is twice the size since the coefficient will be the same size
--           coef_width:integer:=16;--Barker code is used as coefficient and is converted to 16-bit width
--           guard: integer:=0;
           coeficient : Coeficient_type;
           tap:integer:=13 --13-chip barker sequence was specified and so this is used
           
         );    
 port(  
      Din:in integer; -- input data  
      Clk:in std_logic; -- input clk  
      reset:in std_logic; -- input reset  
      Dout:out integer -- output data
     );  
 end FIR_RI;
 
 --End of entity declaration
 -----------------------------------------------------------------------------------------------------------
 
 ------------------------------------------------------------------------------------------------------------  
 architecture behaivioral of FIR_RI is 
 
------------------------------------------------------------------------------------------------------------   
 -- N bit Register component is declared and behaivor is described later. This is used to store signals temporarily  
 component N_bit_Reg   
-- generic (  
--           input_width:integer:=16  
--         );  
   port(  
         Q : out integer;     
         Clk :in std_logic;    
         reset :in std_logic;   
         D :in integer    
       );  
 end component;
 
 
 -------------------------------------------------------------------------------------------------------------
 
 
 
 -- Coefficients are an 11 element array of 16-bit elements i.e. Barker Code
 --In this situation we are using the largest possible negative and positive numbers i.e. 2^15-1 and 2^15  
 -- as representing -1 and 1. We then flip the Barker Sequence to gain the impulse response -1 1 -1 -1 1 -1 -1 -1 1 1 1
 
  
-- type Coeficient_type is array (1 to tap) of integer;  
-- -----------------------------------FIR filter coefficients----------------------------------------------------------------  
-- constant coeficient: coeficient_type :=   
--                               (    
----                                    "1000000000000000",  
--                                    "0111111111111111",  
--                                    "1000000000000000",  
--                                    "1000000000000000",  
--                                    "0111111111111111",  
--                                    "1000000000000000",  
--                                    "1000000000000000",  
--                                    "1000000000000000",  
--                                    "0111111111111111",  
--                                    "0111111111111111",  
--                                    "0111111111111111" 
                                    
--                                    "1111111111111111",
--                                    "0000000000000001",
--                                    "1111111111111111",
--                                    "1111111111111111",
--                                    "0000000000000001",
--                                    "1111111111111111",
--                                    "1111111111111111",
--                                    "1111111111111111",
--                                    "0000000000000001",
--                                    "0000000000000001",
--                                    "0000000000000001" 
                                    
--                                    X"FFFF",
--                                    X"0001",
--                                    X"FFFF",
--                                    X"FFFF",
--                                    X"0001",
--                                    X"FFFF",
--                                    X"FFFF",
--                                    X"FFFF",
--                                    X"0001",
--                                    X"0001",
--                                    X"0001"
-- All of the above represents  the same sequence. Below sequence represents the inverted sequence i.e. -1 and 1 switched
--                                     X"0001",
--                                     X"FFFF",
--                                     X"0001",
--                                     X"0001",
--                                     X"FFFF",
--                                     X"0001",
--                                     X"0001",
--                                     X"0001",
--                                     X"FFFF",
--                                     X"FFFF",
--                                     X"FFFF"
--                                        -1,
--                                         1,
--                                        -1,
--                                        -1,
--                                         1,
--                                        -1,
--                                        -1,
--                                        -1,
--                                         1,
--                                         1,
--                                         1 

                          --              1,1,1,-1,-1,-1,1,-1,-1,1,-1
                        --  +1, +1, +1, +1, +1, -1, -1, +1, +1, -1, +1, -1, +1
  --                        1, -1, 1, -1, 1, 1, -1, -1, 1, 1, 1, 1, 1
--                          --  1,  0, 1, 0,  1, 1,  0,  0, 1, 1, 1, 1, 1                                                                       
--                                   );  
                                   
 ----------------------------------------------------------------------------------------------
 
 
                                      
 type shift_reg_type is array (0 to tap-1) of integer;  
 signal shift_reg : shift_reg_type;
   
 type mult_type is array (0 to tap-1) of integer;  
 signal mult : mult_type;
   
 type ADD_type is array (0 to tap-1) of integer;  
 signal ADD: ADD_type;
 
   
 begin  
 -- First input is sent to the first element of the array for shift register
        shift_reg(0)     <= Din;  
           mult(0)<= Din*coeficient(1);  
           ADD(0)<= Din*coeficient(1);
           
--Actual FIR filter creates other taps and applies MAC operations based on other filter coefficients             
           GEN_FIR:  
           for i in 0 to tap-2 generate  
           begin  
                 -- N-bit reg unit  
                 N_bit_Reg_unit : N_bit_Reg 
                    
                 port map ( Clk => Clk,   
                                    reset => reset,  
                                    D => shift_reg(i),  
                                    Q => shift_reg(i+1)  
                                    );       
                -- filter multiplication  
                mult(i+1)<= shift_reg(i+1)*coeficient(i+2);  
                -- filter conbinational addition  
                ADD(i+1)<=ADD(i)+mult(i+1);
                  
           end generate GEN_FIR;  
           Dout <= ADD(tap-1);  
 end Architecture;  

--End of actual filter description
-------------------------------------------------------------------------------------------------------------------------

--Beginning of register description
 Library IEEE;  
 USE IEEE.Std_logic_1164.all;  
 
 -- N-bit Register in VHDL 
 entity N_bit_Reg is   
   port(  
    Q : out integer;    
    Clk :in std_logic;    
    reset :in std_logic;  
    D :in integer    
   );  
 end N_bit_Reg;
   
 architecture Behavioral of N_bit_Reg is   
 begin   
      process(Clk,reset)  
      begin   
           if (reset = '1') then  
                Q <= 0;  
        elsif ( rising_edge(Clk) ) then  
                Q <= D;   
       end if;      
      end process;   
 end Behavioral;