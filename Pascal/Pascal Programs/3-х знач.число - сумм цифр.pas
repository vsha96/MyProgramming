program ABC;

var
i,a,b,c:integer;

begin
  read(i);
  a:=i div 100;
  b:=(i-a*100) div 10;
  c:=(i-a*100-b*10);
  writeln(a+b+c);
end.