program ABEC;

var

m,x,y:integer;

begin

m:=32567;
for x:=-10 to 10 do begin
y:=7*x*x*x*x*x-3*x*x+7;
if m>y then
m:=y;
end;
writeln(m);


end.

{ ايفان }