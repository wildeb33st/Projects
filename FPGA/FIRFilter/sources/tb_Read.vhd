LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
LIBRARY std;
USE std.textio.all;

ENTITY ReadFile IS
  generic(
    --set numOfBits to 16 to reflect format for data
    --numOfBits : integer;
    file_name : string
    );
  port(
    data : out integer;
    dv: out std_logic;
    rst : in std_logic;
    rfd : in std_logic;
    clk : in std_logic
    );
END ENTITY ReadFile;

--

ARCHITECTURE a OF ReadFile IS
  constant   log_file_rd : string  := file_name;

  file file_rd: TEXT open read_mode is log_file_rd;
BEGIN
  read_data: process(clk,rst)
    variable s: integer;
    variable l: line;
    
  begin
    if (rst = '1') then
      data <= 0;
      dv <= '0';
    elsif(rising_edge(clk)) then
      if rfd='1' then
        readline(file_rd, l);
        read (l, s);
        --data <= CONV_STD_LOGIC_VECTOR(s,numOfBits);
        data <= s;
        dv <= '1';        
      else
        dv <= '0';
      end if;
    end if;
  end process;
END ARCHITECTURE a;