program RakDelivery;

var

  f1,f2,g  :integer;
  f3,m,a,b :real   ;
  
begin
writeln('УЧТИТЕ, по условию нельзя задавать A и B > 90°');
  g:=10;
  
  writeln('угол А');
  readln(a);
  a:=a*Pi/180;
  
  writeln('угол B');
  readln(b);
  b:=b*Pi/180;
  
  writeln('сила лебедя');
  readln(f1);
  
  writeln('сила щуки');
  readln(f2);
  
      f3:=f1*sin(a)+f2*sin(b);
      writeln('сила рака');
      writeln(f3);
      
      m:=(f1*cos(a)-f2*cos(b)-f1*sin(a)-f2*sin(b)+f3)/g;
      writeln('масса воза');
      writeln(m);
end.