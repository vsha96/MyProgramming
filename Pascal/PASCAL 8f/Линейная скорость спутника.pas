program PE (input,output);
var
v,g,m,r,h: real;

begin
g:=6.672*0.0000000001;
m:=5.976*10000000000*10000000000000;
r:=6371030;
readln(h);
v:=sqrt(g*m/(r+h));
writeln(v);

end.

{ ايفان }
