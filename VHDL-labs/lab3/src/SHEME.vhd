-------------------------------------------------------------------------------
--
-- Title       : interface
-- Design      : lab3
-- Author      : maksym.popov.ki.2021@lpnu.ua
-- Company     : Lviv Polytechnic National University
--
-------------------------------------------------------------------------------
--
-- File        : c:\My_Designs\lab3\src\SHEME.vhd
-- Generated   : Sat Apr 15 17:24:18 2023
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
        Y : out STD_LOGIC;
        X : in STD_LOGIC_VECTOR(0 to 2)
    );
end interface;

architecture behaviour of interface is
  		signal A : std_logic;
        signal B : std_logic;
        signal C : std_logic;
        signal D : std_logic;
        signal E : std_logic;
        signal F : std_logic;
begin

    -- enter your statements here --
    process (X)

	begin
        A <= transport not X(0) after 5 ns;
        B <= transport A or X(1) after 10 ns;
        C <= transport not (A or X(2)) after 10 ns;
        D <= transport B and C after 20 ns;
        E <= transport not (C xor X(2)) after 10 ns;
        F <= transport B xor D after 10 ns;
        Y <= transport not (E and F) after 10 ns;
    end process;

end behaviour;
