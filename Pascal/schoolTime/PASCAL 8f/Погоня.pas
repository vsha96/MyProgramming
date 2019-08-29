program pogonya;
var
Vv1,Vv0      : integer;
Xz,Xv,t,Vv :    real;

begin
writeln('Нач скорость волка');
  readln(Vv0);
writeln('Конеч скорость волка');
  readln(Vv1);
 //x=0
 Xz:=1;
 t:=0;
 Vv:=Vv0;
 Xv:=0;
  while Xz>Xv do begin
    t   :=t+0.1;
    Xz  :=1+t;
    Xv  :=Xv+Vv*0.1;
    Vv  :=Vv1-(Vv1-Vv0)*(1+t-Xv);
  end;
  writeln(t);
end.