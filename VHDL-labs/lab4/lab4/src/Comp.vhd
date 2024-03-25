-------------------------------------------------------------------------------
--
-- Title       : comp
-- Design      : lab4
-- Author      : maksym.popov.ki.2021@lpnu.ua
-- Company     : Lviv Polytechnic National University
--
-------------------------------------------------------------------------------
--
-- File        : c:\My_Designs\lab4\lab4\src\Comp.vhd
-- Generated   : Sun Apr 16 19:11:33 2023
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
--{entity {comp} architecture {comp}}


library IEEE;
use IEEE.std_logic_1164.all;

entity comp is
   port(
     -- CLK : inout STD_LOGIC;
     Ainout : inout STD_LOGIC;
     Bout : out STD_LOGIC
       );
end comp;

--}} End of automatically maintained section

architecture comp of comp is
signal CLK : std_logic :='0';
begin

  -- enter your statements here --
  --begin
    Pr_CLK: process--(CLK)
	begin
		CLK <= not CLK; 
		wait for 20 ns;
    end process Pr_CLK;
    Pr_A: process--(CLK)
    begin
		while true loop
			if CLK = '1' then
				wait for 20 ns;
				Ainout <= '1';
			elsif CLK = '0' then
				wait for 20 ns;
				Ainout <= '0';
			end if;
			wait on CLK;
		end loop;

      --if CLK'event and CLK ='1' then Ainout<='1' after 5 ns;
      --elsif CLK'event and CLK='0' then Ainout<='0' after 5 ns; 
      --end if;
    end process Pr_A;
	Pr_B: process --(Ainout)
	begin
		wait until Ainout'event;
        Bout <= not Ainout;
        -- if Ainout'event then Bout<= not Ainout;
        -- end if;
    end process Pr_B;
end comp;