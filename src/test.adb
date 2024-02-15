with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Test is
    bool_var1: Boolean;
    bool_var2 :Boolean;
    function test_function(x: in integer) return Boolean is
    begin
        Put(x, 0);
        return true;
    end test_function;
begin
    for i in 1 .. 10 loop
        Put("ici");
        if 3>7 then
            bool_var1 := true;
        else
            bool_var1 := false;
        end if;
    end loop;
end Test;
    