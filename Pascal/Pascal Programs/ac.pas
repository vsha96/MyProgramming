program AC;

var
  v:   real;
  g:   real;
  s:   real;
  x:   real;
  ms:  real;
  mx:  real;
  mxg: integer;

begin
  writeln('¬ведите скорость: ');
  readln(v);
  x  := 0;
  g  := 9.8;
  ms := 0;
  mx := 0;
  while x < 3.14 / 2 do 
  begin
    s := 2 * v * cos(x) * sin(x) / g; 
    if ms < s then
    begin
      ms := s;
      mx := x;
    end;
    x := x + 0.1;
  end;
  mxg := Trunc(mx * (180 / 3.14));
  writeln('”гол: ', mxg,'∞');
end.