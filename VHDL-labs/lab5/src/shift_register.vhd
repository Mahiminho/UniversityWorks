library IEEE;
use IEEE.std_logic_1164.all;

entity reg_8bit is
  port (
    CLK: in std_logic;
    RESET: in std_logic;
    data_in: in std_logic_vector(7 downto 0);
    WE: in std_logic;
    RE: in std_logic;
  	SHIFT: in std_logic;
    data_out: out std_logic_vector(7 downto 0)
  );
end entity;

architecture Behavioral of reg_8bit is
  signal reg_data: std_logic_vector(7 downto 0);
begin
  process(CLK, RESET)    
  variable temp : std_logic := '0';
  begin
    if RESET = '1' then
      reg_data <= (others => '0');
    elsif rising_edge(clk) then   
      if (WE = '1' and RE = '1') or (WE = '0' and RE = '0') then
        data_out <= "ZZZZZZZZ";
      else
        if WE = '1' then
          reg_data <= data_in;
        end if;
        if RE = '1' then
          data_out <= reg_data;
        end if;
        if SHIFT = '1' then   
          temp := reg_data(7);
          for i in 7 downto 1 loop
                      reg_data(i) <= reg_data(i-1);
          end loop;
          reg_data(0) <= temp;
        end if;
      end if;
    end if;
  end process;
end architecture;