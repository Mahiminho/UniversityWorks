library IEEE;
use IEEE.std_logic_1164.all;

entity lcd_converter is
  port (
    X: in std_logic_vector(3 downto 0);
    LCD: out std_logic_vector(6 downto 0)
  );
end lcd_converter;

architecture Behavioral of lcd_converter is
begin
  process(X)
  begin
    case X is
      when "0000" =>
        LCD <= "0000000";
      when "0001" =>
        LCD <= "1000000";
      when "0010" =>
        LCD <= "0100000";
      when "0011" =>
        LCD <= "1100000";
      when "0100" =>
        LCD <= "0010000";
      when "0101" =>
        LCD <= "1010000";
      when "0110" =>
        LCD <= "0110000";
      when "0111" =>
        LCD <= "1110000";
      when "1000" =>
        LCD <= "0001000";
      when "1001" =>
        LCD <= "1001000";
      when "1010" =>
        LCD <= "0101000";
      when "1011" =>
        LCD <= "1101000";
      when "1100" =>
        LCD <= "0011000";
      when "1101" =>
        LCD <= "1011000";
      when "1110" =>
        LCD <= "0111000";
      when "1111" =>
        LCD <= "1111000";
      when others =>
        LCD <= "-------"; -- помилка
    end case;
  end process;
end Behavioral;
