program pogonya;
uses GraphABC;
var
Vv1,Vv0,Xz,Xv,t,Vv,Vz     : integer;

begin
writeln('Нач скорость волка');
  readln(Vv0);
writeln('Конеч скорость волка');
  readln(Vv1);
writeln('Cкорость зайца');
  readln(Vz);
 //x=0
 t:=0;
 Xz:=1;
 Xv:=0;
 Vv:=Vv0;
  while Xv<Xz do begin
      t   :=t+1;
      Xz  :=100+Vz*t;
      Xv  :=Xv+Vv*t;
      
      clearwindow;
      circle(xv,100,50);
      //floodfill(100+xv,100,clsilver);
      
      circle(xz,100,20);
      //floodfill(30+xz,100,clgray);
     sleep(100);
  end;

  
end.