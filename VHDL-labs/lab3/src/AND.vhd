-------------------------------------------------------------------------------
--
-- Title       : interface
-- Design      : lab3
-- Author      : maksym.popov.ki.2021@lpnu.ua
-- Company     : Lviv Polytechnic National University
--
-------------------------------------------------------------------------------
--
-- File        : c:\My_Designs\lab3\src\AND.vhd
-- Generated   : Sat Apr 15 16:31:06 2023
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
		 AND_IN1 : in STD_LOGIC;
		 AND_IN2 : in STD_LOGIC;
		 AND_OUT : out STD_LOGIC;
		 Input_delay : time := 10 ns
	     );
end interface;

--}} End of automatically maintained section

architecture behaviour of interface is
begin

	-- enter your statements here --
	process (AND_IN1, AND_IN2)
  begin
    wait for Input_delay;
    AND_OUT <= AND_IN1 and AND_IN2; 
  end process;

end behaviour;
