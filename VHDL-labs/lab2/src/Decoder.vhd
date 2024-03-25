-------------------------------------------------------------------------------
--
-- Title       : decoder
-- Design      : lab_2_mks
-- Author      : maksym.popov.ki.2021@lpnu.ua
-- Company     : Lviv Polytechnic National University
--
-------------------------------------------------------------------------------
--
-- File        : c:\My_Designs\lab_2_mks\src\Decoder.vhd
-- Generated   : Mon Apr 10 21:31:32 2023
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
--{entity {decoder} architecture {Behavioral}}

library IEEE;
use IEEE.std_logic_1164.all;

entity decoder is
	 port(
		 DataIn : in STD_LOGIC_VECTOR(3 downto 0);
		 Output : out STD_LOGIC_VECTOR(6 downto 0)
	     );
end decoder;

--}} End of automatically maintained section

architecture Behavioral of decoder is
begin

	-- enter your statements here -- 
	with DataIn select
	Output <= "1111110" when "0000",
			"0110000" when "0001",
			"1101101" when "0010",
			"1111001" when "0011",
			"0110011" when "0100",
			"1011011" when "0101",
			"1011111" when "0110",
			"1110000" when "0111",
			"1111111" when "1000",
			"1111011" when "1001",
			"0000000" when others;


end Behavioral;
