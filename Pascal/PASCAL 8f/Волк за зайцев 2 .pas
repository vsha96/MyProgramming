program qq2 ;
uses GraphABC;
var
Vv1,Vv0,Xz,Xv,T,Vv,Vz      : integer;

begin
writeln('Нач скорость волка');                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
  readln(Vv0);
writeln('Конеч скорость волка');
  readln(Vv1);
  writeln('Скорость зайца');
  readln(Vz);
 //x=0
 Xz:=1;
  T:=0;
 Vv:=Vv0;;
 Xv:=0;
  while Xz>Xv do begin
    T   :=T+1;
    Xz  :=100+T;
    Xv  :=Xv+Vv*T;
    Vv  :=Vv1-(Vv1-Vv0)*(1+T-Xv);
    
    
    clearwindow;
    circle(Xv,100,50);
    //floodfill(100+Xv,100,clRed);
    
    circle(Xz,100,20);
    //floodfill(30+Xz,100,clLime);
    Sleep(100);
  end;
  writeln(T);
  end.
