Library IEEE;  
 USE IEEE.Std_logic_1164.all;   
 USE IEEE.Std_logic_signed.all; 


 -- package declaration
 --This is used to pass the coeffient array as a generic. Without this library it could not be done.
package coeff_pkg is

     type Coeficient_type is array (1 to 13) of integer range -1 to 1;

end package coeff_pkg;