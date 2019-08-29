program Montekarlo;

var
  N: integer;
  m:    real;
  x:    real;
  y:    real;
  p:    real;
  i: integer;
  
begin
  writeln('Введите кол-во точек от 1 до N = ' );  
  readln(N);
  m :=0;
  
  for i:= 1 to N do
  
    begin
    x := random(2)-1;
    y := random(2)-1;
      if x*x + y*y <= 1 then  begin
      m := m + 1;
      end;
    p := (4 * m) / N;
    end;
    writeln('Пи = ', p);
  
end.
{ ايفان }

