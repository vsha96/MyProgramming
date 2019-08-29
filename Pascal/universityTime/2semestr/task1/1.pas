program class;
type TF = function(x:real):real; {functional type}
var eps1,eps2:real;
   a,b,s:real;
   x1,x2,x3:real;
   I1,I2,I3:real;
procedure swap(var a,b:real);
   var c:real;
   begin
	c:=a; a:=b; b:=c;
   end;

function f1(x:real):real;
   begin
	f1:=3*(0.5/(x+1)+1);
   end;
function f2(x:real):real;
   begin
	f2:=2.5*x-9.5;
   end;
function f3(x:real):real;
   begin
	f3:=5/x;
   end;

function root(f,g:TF; a,b,eps1:real):real;
   var c,fab,fa,fb:real;
   function fr(x:real):real; {function, where is my root?}
	begin
	   fr:=f(x)-g(x);
	end;
   begin
	if a>b then swap(a,b);
	{there I'm finding the root}
	fa:=fr(a); fb:=fr(b);
	fab:=fr(a/2+b/2);
	c:=(a*fb-b*fa)/(fb-fa);
	if (fa>0) and (fab>fa/2+fb/2) or (fa<0) and (fab<fa/2+fb/2) then
	   while (abs(fr(c))>=eps1) do
		begin
		   a:=c;
		   fa:=fr(a);
		   c:=(a*fb-b*fa)/(fb-fa);
		end
	else 
	   while (abs(fr(c))>=eps1) do
		begin
		   b:=c;
		   fb:=fr(b);
		   c:=(a*fb-b*fa)/(fb-fa);
		end;
	root:=c;
   end;
function integral(f:TF; a,b,eps2:real):real;
   const p=1/3;
   var n:integer;
	I1,I2:real;
   function integrate({f:TF;} n:integer):real;
	var s,h:real; i:integer;
	begin
	   h:=(b-a)/n; s:=0;
	   for i:=0 to n-1 do
		begin
		   s:=s+0.5*h*(f(a+i*h)+f(a+(i+1)*h));
		end;
	   integrate:=s;
	end;
   begin
	if a>b then swap(a,b);
	n:=20;
	I1:=integrate(n);
	I2:=integrate(2*n);
	while p*abs(I1-I2)>eps2 do
	   begin
		n:=2*n;
		I1:=integrate(n);
		I2:=integrate(2*n);
	   end;
	integral:=I2;
   end;

begin
   a:=1; b:=8;
   write('введите eps1 для поиска корня = '); readln(eps1);
   x1:=root(@f1,@f2,a,b,eps1);
   x2:=root(@f2,@f3,a,b,eps1);
   x3:=root(@f1,@f3,a,b,eps1);
   
   writeln('f1 пересекает f2 =',x1:1:5);
   writeln('f2 пересекает f3 =',x2:1:5);
   writeln('f3 пересекает f1 =',x3:1:5);
   
   write('введите eps2 для точности интеграла = '); readln(eps2);
   
   I1:=integral(@f1,x1,x3,eps2);
   I2:=integral(@f2,x1,x2,eps2);
   I3:=integral(@f3,x3,x2,eps2);
   s:=abs(abs(I1-I2)-I3);
   writeln('I1 = ',I1:2:5,' I2 = ',I2:2:5,' I3 = ',I3:2:5);
   writeln('площадь замкнутой фигуры = ',s:2:5);
   
end.