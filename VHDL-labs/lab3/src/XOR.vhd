-------------------------------------------------------------------------------
--
-- Title       : interface
-- Design      : lab3
-- Author      : maksym.popov.ki.2021@lpnu.ua
-- Company     : Lviv Polytechnic National University
--
-------------------------------------------------------------------------------
--
-- File        : c:\My_Designs\lab3\src\XOR.vhd
-- Generated   : Sat Apr 15 17:03:00 2023
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
		 XOR_IN1 : in STD_LOGIC;
		 XOR_IN2 : in STD_LOGIC;
		 XOR_OUT : out STD_LOGIC;
		 Input_delay : time := 10 ns
	     );
end interface;

--}} End of automatically maintained section

architecture behaviour of interface is
begin

	-- enter your statements here --  
	process (XOR_IN1, XOR_IN2)
  begin
    wait for Input_delay;
    XOR_OUT <= XOR_IN1 xor XOR_IN2; 
  end process;

end behaviour;
