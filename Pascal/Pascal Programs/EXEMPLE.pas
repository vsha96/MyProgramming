uses graphABC;
const
x1=-10;
x2=10;
var
x,dx,y1,y2,y:real;
mx,my,x0,y0,px,py1,py2,i,c:integer;
s:string;
begin
X0:=windowwidth div 2;{начало координат}
Y0:=windowheight -70;
mx:=round((windowwidth)/(20));
my:=round((windowheight-70)/x2);
line(25,y0,windowwidth-25,y0); {ось Х}
line(x0,y0,x0,10); {ось У}
for i:=1 to x2 do
   begin
    line(x0-3,y0-i*my,x0+3,y0-i*my);     {засечки на оси У}
    line(x0+i*mx,y0-3,x0+i*mx,y0+3); {засечки на оси Х}
    line(x0-i*mx,y0-3,x0-i*mx,y0+3);
    {подпись оси У}
    str(i,s);
    textout(x0+5,y0-i*my,s);{соответственно засечкам}
    {подпись оси Х}
    textout(x0+i*mx,y0+10,s);
    textout(x0-i*mx,y0+10,'-'+s);
   end;
{подписи концов осей}
textout(windowwidth-25,y0-15,'X');
textout(x0+10,5, 'Y');
textout(x0,y0+10, '0');
dx:=0.001;
x:=x1;
while x<=x2 do
   begin
     px:=x0+round(x*mx); {изменение по оси Х}
     y1:=abs(x); {график}
     py1:=y0-round(y1*my);
     Putpixel (px,py1,clRed);
     x:=x+dx; {наращиваем х}
   end;
readln;
end.
