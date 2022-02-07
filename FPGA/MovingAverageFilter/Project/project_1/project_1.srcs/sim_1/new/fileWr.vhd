LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
LIBRARY std;
USE std.textio.all;

ENTITY WriteFile_full IS
  generic(
    numOfBits : integer;
    file_name : string
    );
  port(
    clk,dv,sign : in std_logic;
    DataIn : in std_logic_vector ((numOfBits-1) downto 0)
    );
END ENTITY WriteFile_full;

--
ARCHITECTURE a OF WriteFile_full IS
  constant   log_file1 : string  := file_name;	
  
  file file_wr: TEXT open write_mode is log_file1;
BEGIN
  write_data : process(clk)
    variable l2 : line;
  begin
    if(rising_edge(clk)) then
      if dv = '1' then
        if sign='0' then
          write (l2, CONV_INTEGER(UNSIGNED(DataIn)));
          writeline(file_wr, l2);
        else
          write (l2, CONV_INTEGER(SIGNED(DataIn)));
          writeline(file_wr, l2);
        end if;
      end if;
    end if;
  end process;
END ARCHITECTURE a;