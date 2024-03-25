-------------------------------------------------------------------------------
--
-- Title       : No Title
-- Design      : lab7
-- Author      : maksym.popov.ki.2021@lpnu.ua
-- Company     : Lviv Polytechnic National University
--
-------------------------------------------------------------------------------
--
-- File        : c:\My_Designs\lab7\lab7\compile\test_diagram.vhd
-- Generated   : Sat Apr 22 21:44:59 2023
-- From        : c:/My_Designs/lab7/lab7/src/test_diagram.bde
-- By          : Bde2Vhdl ver. 2.6
--
-------------------------------------------------------------------------------
--
-- Description : 
--
-------------------------------------------------------------------------------
-- Design unit header --
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_signed.all;
use IEEE.std_logic_unsigned.all;

entity test_diagram is
  port(
       CLK : in STD_LOGIC;
       WE : in STD_LOGIC;
       X : in STD_LOGIC_VECTOR(31 downto 0);
       LCD1 : out STD_LOGIC_VECTOR(6 downto 0);
       LCD2 : out STD_LOGIC_VECTOR(6 downto 0);
       LCD3 : out STD_LOGIC_VECTOR(6 downto 0);
       LCD4 : out STD_LOGIC_VECTOR(6 downto 0);
       LCD5 : out STD_LOGIC_VECTOR(6 downto 0);
       LCD6 : out STD_LOGIC_VECTOR(6 downto 0);
       LCD7 : out STD_LOGIC_VECTOR(6 downto 0);
       LCD8 : out STD_LOGIC_VECTOR(6 downto 0)
  );
end test_diagram;

architecture test_diagram of test_diagram is

---- Component declarations -----

component demultiplexer
  port(
       X : in STD_LOGIC_VECTOR(31 downto 0);
       CLK : in STD_LOGIC;
       Y0 : out STD_LOGIC_VECTOR(3 downto 0);
       Y1 : out STD_LOGIC_VECTOR(3 downto 0);
       Y2 : out STD_LOGIC_VECTOR(3 downto 0);
       Y3 : out STD_LOGIC_VECTOR(3 downto 0);
       Y4 : out STD_LOGIC_VECTOR(3 downto 0);
       Y5 : out STD_LOGIC_VECTOR(3 downto 0);
       Y6 : out STD_LOGIC_VECTOR(3 downto 0);
       Y7 : out STD_LOGIC_VECTOR(3 downto 0)
  );
end component;
component lcd_converter
  port(
       X : in STD_LOGIC_VECTOR(3 downto 0);
       LCD : out STD_LOGIC_VECTOR(6 downto 0)
  );
end component;
component parallel_register
  port(
       X : in STD_LOGIC_VECTOR(31 downto 0);
       WE : in STD_LOGIC;
       CLK : in STD_LOGIC;
       Y : out STD_LOGIC_VECTOR(31 downto 0)
  );
end component;

---- Signal declarations used on the diagram ----

signal BUS144 : STD_LOGIC_VECTOR(31 downto 0);
signal BUS148 : STD_LOGIC_VECTOR(3 downto 0);
signal BUS183 : STD_LOGIC_VECTOR(3 downto 0);
signal BUS198 : STD_LOGIC_VECTOR(3 downto 0);
signal BUS213 : STD_LOGIC_VECTOR(3 downto 0);
signal BUS221 : STD_LOGIC_VECTOR(3 downto 0);
signal BUS229 : STD_LOGIC_VECTOR(3 downto 0);
signal BUS237 : STD_LOGIC_VECTOR(3 downto 0);
signal BUS245 : STD_LOGIC_VECTOR(3 downto 0);

begin

----  Component instantiations  ----

U10 : lcd_converter
  port map(
       X => BUS221,
       LCD => LCD5
  );

U11 : lcd_converter
  port map(
       X => BUS237,
       LCD => LCD7
  );

U12 : lcd_converter
  port map(
       X => BUS245,
       LCD => LCD8
  );

U13 : lcd_converter
  port map(
       X => BUS183,
       LCD => LCD2
  );

U14 : lcd_converter
  port map(
       X => BUS213,
       LCD => LCD4
  );

U15 : lcd_converter
  port map(
       X => BUS229,
       LCD => LCD6
  );

U6 : parallel_register
  port map(
       X => X,
       WE => WE,
       CLK => CLK,
       Y => BUS144
  );

U7 : demultiplexer
  port map(
       X => BUS144,
       CLK => CLK,
       Y0 => BUS148,
       Y1 => BUS183,
       Y2 => BUS198,
       Y3 => BUS213,
       Y4 => BUS221,
       Y5 => BUS229,
       Y6 => BUS237,
       Y7 => BUS245
  );

U8 : lcd_converter
  port map(
       X => BUS148,
       LCD => LCD1
  );

U9 : lcd_converter
  port map(
       X => BUS198,
       LCD => LCD3
  );


end test_diagram;
