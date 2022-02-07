--Low pass filter based on running average

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE ieee.std_logic_arith.all;

entity lab111 is
    Port ( clk : in STD_LOGIC;
           din : in STD_LOGIC_VECTOR (15 downto 0);
           dout : out STD_LOGIC_VECTOR (15 downto 0);
           dv : in std_logic
         );
end lab111;

architecture Behavioral of lab111 is
    type tdelay is array (7 downto 0) of std_logic_vector(15 downto 0);
    signal sdelay    : tdelay:=(others => (others => '0'));
    signal res       : std_logic_vector(18 downto 0):=(others => '0');


begin

process (clk) begin
	if rising_edge(clk) then
	
		  if dv = '1' then
		     -- The following line appends din to each element of sdelay array, thereby producing a buffering effect
			sdelay <= din & sdelay(7 downto 1);
		  
		  	
			--the following line is the accumulator and essentially employs a shortcut to give us the updated value of the sum
			-- for the new value that has been entered
		    res <= (SIGNED(res) + signed(din) - SIGNED(sdelay(0)));
		  end if;  
	--Finally the output is based on the idea that any multiplication or division operation in binary when dividing by 2
		    -- is simply a shift to either the right or left and so only part of the accumulator result is used i.e. equivalent
		    --to three left shifts
		    dout <= res(18 downto 3);
		
		   
	end if;
end process;

 

end architecture;