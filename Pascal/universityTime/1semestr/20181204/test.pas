program test;
type ar = array['a'..'z'] of integer;
var m: ar;
   c: char;
   i: integer;
begin
   i:=0;
   for c:='a' to 'z' do
	begin
	   i:=i+1;
	   m[c]:=i;
	end;
   
   for c:='a' to 'z' do
	write(m[c]:6);
   writeln;
end.