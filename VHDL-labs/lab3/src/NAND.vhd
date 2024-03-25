-------------------------------------------------------------------------------
--
-- Title       : interface
-- Design      : lab3
-- Author      : maksym.popov.ki.2021@lpnu.ua
-- Company     : Lviv Polytechnic National University
--
-------------------------------------------------------------------------------
--
-- File        : c:\My_Designs\lab3\src\NAND.vhd
-- Generated   : Sat Apr 15 16:33:53 2023
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
		 NAND_IN1 : in STD_LOGIC;
		 NAND_IN2 : in STD_LOGIC;
		 NAND_OUT : out STD_LOGIC;
		 Input_delay : time := 10 ns
	     );
end interface;

--}} End of automatically maintained section

architecture behaviour of interface is
begin

	-- enter your statements here --  
		process (NAND_IN1, NAND_IN2)
  begin
    wait for Input_delay;
    NAND_OUT <= not(NAND_IN1 and NAND_IN2); 
  end process;

end behaviour;
