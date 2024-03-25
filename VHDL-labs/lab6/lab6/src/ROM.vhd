-------------------------------------------------------------------------------
--
-- Title       : ROM
-- Design      : lab6
-- Author      : maksym.popov.ki.2021@lpnu.ua
-- Company     : Lviv Polytechnic National University
--
-------------------------------------------------------------------------------
--
-- File        : c:\My_Designs\lab6\lab6\src\ROM.vhd
-- Generated   : Wed Apr 19 22:45:17 2023
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
--{entity {ROM} architecture {ROM}}
library IEEE;
use IEEE.std_logic_1164.all;
use ieee.numeric_std.ALL;

entity ROM is
	port (
        Addr: in std_logic_vector(3 downto 0); -- вхідний 4-розрядний порт адреси ПЗП
        CEO: in std_logic; -- вхідний порт дозволу зчитування ПЗП
        Dout: out std_logic_vector(3 downto 0) -- вихідний 4-розрядний порт даних
    );
end ROM;

--}} End of automatically maintained section

architecture ROM of ROM is
type t_array_rom is array (0 to 3) of std_logic_vector(3 downto 0);
signal array_rom  : t_array_rom;
begin
	array_rom(0) <= "1010";
  	array_rom(1) <= "1101";
  	array_rom(2) <= "1001";
  	array_rom(3) <= "1111";

	-- enter your statements here --
	process (Addr, CEO, array_rom)
	begin
	    if CEO = '1' then -- перевірка на дозвіл зчитування
	        Dout <= array_rom(to_integer(unsigned(Addr))); -- зчитування даних з відповідної комірки
	    end if;
	end process;

end ROM;




