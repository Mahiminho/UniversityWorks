library IEEE;
use IEEE.std_logic_1164.all;

entity parallel_register is
    port(
        X   : in  std_logic_vector(31 downto 0);
        WE  : in  std_logic;
        CLK : in  std_logic;
        Y   : out std_logic_vector(31 downto 0)
    );
end entity parallel_register;

architecture Behavioral of parallel_register is
    signal reg : std_logic_vector(31 downto 0);  -- проміжний регістр
begin
    process(CLK)
    begin
        if rising_edge(CLK) then  -- обробка лише під час фронту сигналу синхронізації
            if WE = '1' then  -- дозвіл на запис
                reg <= X;  -- записуємо вміст вхідного порту X у проміжний регістр
            end if;
        end if;
    end process;

    Y <= reg;  -- передача значення з проміжного регістру на вихідний порт Y
end architecture Behavioral;
