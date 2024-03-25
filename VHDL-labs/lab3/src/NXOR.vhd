-------------------------------------------------------------------------------
--
-- Title       : interface
-- Design      : lab3
-- Author      : maksym.popov.ki.2021@lpnu.ua
-- Company     : Lviv Polytechnic National University
--
-------------------------------------------------------------------------------
--
-- File        : c:\My_Designs\lab3\src\NXOR.vhd
-- Generated   : Sat Apr 15 17:06:07 2023
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
		 NXOR_IN1 : in STD_LOGIC;
		 NXOR_IN2 : in STD_LOGIC;
		 NXOR_OUT : out STD_LOGIC;
		 Input_delay : time := 10 ns
	     );
end interface;

--}} End of automatically maintained section

architecture behaviour of interface is
begin

	-- enter your statements here --
	process (NXOR_IN1, NXOR_IN2)
  begin
    wait for Input_delay;
    NXOR_OUT <= not(NXOR_IN1 xor NXOR_IN2); 
  end process;

end behaviour;
