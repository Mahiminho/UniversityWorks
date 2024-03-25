-------------------------------------------------------------------------------
--
-- Title       : parallel_register
-- Design      : lab5
-- Author      : maksym.popov.ki.2021@lpnu.ua
-- Company     : Lviv Polytechnic National University
--
-------------------------------------------------------------------------------
--
-- File        : c:\My_Designs\lab5\src\Parallel_register.vhd
-- Generated   : Mon Apr 17 19:38:38 2023
-- From        : interface description file
-- By          : Itf2Vhdl ver. 1.22
--
-------------------------------------------------------------------------------
--
-- Description : 
--
-------------------------------------------------------------------------------

--{{ Section below this comment is automatically maintained
--   and may be overwritten
--{entity {parallel_register} architecture {Behavioral}}

library IEEE;
use IEEE.std_logic_1164.all;

entity reg_8bit is
  port (
    CLK : in std_logic;
    RESET : in std_logic;
    data_in: in std_logic_vector(7 downto 0);
    WE: in std_logic;
    RE: in std_logic;
    data_out: out std_logic_vector(7 downto 0)
  );
end entity;

architecture Behavioral of reg_8bit is
  signal reg_data : std_logic_vector(7 downto 0);
begin
  process(CLK, RESET)
  begin
    if RESET = '1' then
      reg_data <= (others => '0');
    elsif rising_edge(CLK) then   
    if (WE = '1' and RE = '1') or (WE = '0' and RE = '0') then
      data_out <= "ZZZZZZZZ";
    else
      if WE = '1' then
            reg_data <= data_in;
          end if;
          if RE = '1' then
            data_out <= reg_data;
          end if;  
    end if;
    end if;
  end process;
end architecture;