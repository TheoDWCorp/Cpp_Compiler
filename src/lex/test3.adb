with Ada.Text IO; use Ada.Text IO;
with Ada.Integer Text IO; use Ada.Integer Text IO;
procedure Vowels is
    Letter : Character;
    Vowel Count : Integer := 0;
    Y Count : Integer := 0;
begin
    while not End Of File loop
        Get(Letter );
        case Letter is
            when ’A’|’E’| ’ I ’ | ’O’|’U’ |
                ’a’ | ’e’ | ’ i ’ | ’o’ | ’u’ =>
                Vowel Count := Vowel Count + 1;
            when ’Y’|’y’ =>
                Y Count := Y Count + 1;
            when others =>
                null ;
        end case;
    end loop;
    Put(”Total number of vowels = ”); Put(Vowel Count); New Line;
    Put(”Total number of Ys = ”); Put(Y Count); New Line;
end Vowels;