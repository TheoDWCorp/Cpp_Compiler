with Ada.Text_IO; use Ada.Text_IO;

procedure Test is
    bool_var1: boolean;
    bool_var2 :boolean;
    bool_var3 : boolean;
    bool_var4             :                 boolean;
    bool_var5:boolean:=True;
begin
    bool_var4:= not (not (False));
    Put_Line(boolean'Image(bool_var5));
    Put_Line(boolean'Image(bool_var4));
end Test;