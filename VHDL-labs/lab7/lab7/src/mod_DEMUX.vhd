library IEEE;
use IEEE.std_logic_1164.all;

entity demultiplexer is
    port (
        X   : in  std_logic_vector(31 downto 0);
        CLK : in  std_logic;
        Y0  : out std_logic_vector(3 downto 0);
        Y1  : out std_logic_vector(3 downto 0);
        Y2  : out std_logic_vector(3 downto 0);
        Y3  : out std_logic_vector(3 downto 0);
        Y4  : out std_logic_vector(3 downto 0);
        Y5  : out std_logic_vector(3 downto 0);
        Y6  : out std_logic_vector(3 downto 0);
        Y7  : out std_logic_vector(3 downto 0)
    );
end entity demultiplexer;

architecture Behavioral of demultiplexer is
    signal select_bits : std_logic_vector(2 downto 0);
begin
    process(CLK)
    begin
        if rising_edge(CLK) then
            select_bits <= X(2 downto 0);
        end if;
    end process;

    Y0 <= X(3 downto 0) when select_bits = "000" else (others => '0');
    Y1 <= X(7 downto 4) when select_bits = "001" else (others => '0');
    Y2 <= X(11 downto 8) when select_bits = "010" else (others => '0');
    Y3 <= X(15 downto 12) when select_bits = "011" else (others => '0');
    Y4 <= X(19 downto 16) when select_bits = "100" else (others => '0');
    Y5 <= X(23 downto 20) when select_bits = "101" else (others => '0');
    Y6 <= X(27 downto 24) when select_bits = "110" else (others => '0');
    Y7 <= X(31 downto 28) when select_bits = "111" else (others => '0');
end architecture Behavioral;

