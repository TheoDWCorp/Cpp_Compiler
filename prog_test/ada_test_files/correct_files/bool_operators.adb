with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Test is
    bool_var1: Boolean;
    bool_var2 :Boolean;
    bool_var3 : Boolean;
begin
    bool_var1:= 6>=0;
    bool_var2:= 1<=2;
    bool_var3:= 0/=0;
    Put(Boolean'Image((bool_var1=bool_var2)=bool_var3));
end Test;
