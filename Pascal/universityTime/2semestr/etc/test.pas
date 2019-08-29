program test;
type TF = function(x:real):real;
const p=1/3;
var i,n:integer;
   a,b:real;

function f1(x:real):real;
   begin
	f1:=x;
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
   writeln(integral(@f1,5,10,0.1):2:5);
end.