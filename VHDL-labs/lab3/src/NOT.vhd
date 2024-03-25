-------------------------------------------------------------------------------
--
-- Title       : interface
-- Design      : lab3
-- Author      : maksym.popov.ki.2021@lpnu.ua
-- Company     : Lviv Polytechnic National University
--
-------------------------------------------------------------------------------
--
-- File        : c:\My_Designs\lab3\src\NOT.vhd
-- Generated   : Sat Apr 15 15:48:12 2023
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
--{entity {interface} architecture {behaviour}}

library IEEE;
use IEEE.std_logic_1164.all;

entity interface is
	 port(
		 NOT_IN : in STD_LOGIC;
		 NOT_OUT : out STD_LOGIC;
		 Input_delay : time := 5 ns
	     );
end interface;

--}} End of automatically maintained section

architecture behaviour of interface is
begin

	-- enter your statements here --
	process (NOT_IN)
  begin
    wait for Input_delay; 
    NOT_OUT <= not NOT_IN; 
  end process;

end behaviour;
