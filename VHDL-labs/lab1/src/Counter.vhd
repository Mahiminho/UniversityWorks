-------------------------------------------------------------------------------
--
-- Title       : counter
-- Design      : lab_1_mks
-- Author      : maksym.popov.ki.2021@lpnu.ua
-- Company     : Lviv Polytechnic National University
--
-------------------------------------------------------------------------------
--
-- File        : c:\My_Designs\lab_1_mks\src\Counter.vhd
-- Generated   : Mon Apr 10 20:43:11 2023
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
--{entity {counter} architecture {Behavioral}}

library IEEE;
use IEEE.std_logic_1164.all;

entity counter is
	 port(
		 CLK : in STD_LOGIC;
		 RST : in STD_LOGIC;
		 Q : out STD_LOGIC_VECTOR(0 to 3)
	     );
end counter;

--}} End of automatically maintained section

architecture Behavioral of counter is
begin

	 -- enter your statements here --

end Behavioral;
