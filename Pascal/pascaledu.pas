program max;
type
{массивы}
	m = array[1..2] of array[1..3] of integer; 	// можно так 1--
	mm = array[1..2, 1..3] of integer; 		// --1 или так
	vector = array[1..5{const}] of real;
{строки}
	str = packed array[1..n] of char;
	//в freepascal есть тип string 			(не более 255 символов)
var 	a: string; b: string[15]; 			//(тут уже не более 15 символов)
{другое}
type	week = (mon,tue,wed,thu,fri,sat,san); 		{перечислимый тип}
	d: '0'..'5'; 					{ограниченный тип}
	int = integer;
	
const
	a = 5;
var
	x, m, t, max:integer;
	q: real;
	r,l: (right, left); 				{безымянный тип}
	s: integer;
{процедуры}
procedure ReadVector(var a: vector);
var i: integer;
begin
	writeln('Input array which size ',n,': ');
	for i:=1 to n do begin
		read(a[i]);
	end
end;
procedure cube(var x:integer); begin x:=x*x*x; end;
{/процедуры}
{функции} //(значение не может быть сложного типа, только простого или ссылочного
function ch(x: real): real;
var
	p: real;
begin
	p:=exp(x);
	ch:=(p+1/p)/2
end;
function pow(a:real;n:integer):real;begin pow:= exp(n*ln(a)); end;
{/функции}
begin
	read(m,x);
	writeln(a);
	t := m div x; 					{целое от деления}
	t := m mod x; 					{остаток}
	max := maxint; 					{служебное имя}
	s:='hello world!';
	writeln('##### ',s[1..5]); {печатает фрагмент строки}

end.


{-----------}
{***знаковые: integer, shorting, longint, int64}{беззнак: byte, word, longword, qword***}
{функции}{abs(a)=|a|; sqr(a)=a*a; succ(a)=a+1; pred(a)=a-1; ord(a)=a}

{***real***}
{функции}{(-и-)sin(x), cos(x), sqrt(x), arctan(x), ln(x), exp(x)}
{trunc(x), round(x)}

{***boolean***}
{функции}{odd(x) {true:x-нечет,false:x-чет}, succ, pred}

{***char***}
{ord(x) {число}}

{***string***}
{ord(s[0]) = length(s)} //выдает размер строки
{-----------}


{операторы}
{
for i:=1 to/downto 50 do... //
if ... then ... else //
while ... do ... //
repeat
...
until (...); //
case month of
	jan,mar...,dec: k:=31;
	feb: k:=28;
	apr,jun...,nov: k:=30;
end //
}

{операторы перехода}
{
break //
continue //
goto (в программе пишем goto quit; quit:...) //
exit //
}

<<<модули>>>
unit arrays; {файл arrays.pas}
interface
	const N = 5;
	type vector = array[1..N] of integer;
	procedure arrayin(var A:vector);
	procedure arrayout(var A:vector);
implementation
 	procedure arrayin(var A:vector);
 		var i:integer;
 		begin for i:=1 to N do read(A[i]); end;
	procedure arrayout(var A:vector);
		var i:integer;
		begin for i:=1 to N do write(A[i],’ ‘); writeln; end;
end.

{работа с файлами}
type rfile = file of real;
var f: rfile;
   x: real;
begin
   assign(f,'data.txt');
   rewrite(f);
   while not eoln() do
	begin
	   read(x);
	   write(f,x);
	end;
   reset(f);
   while not eof(f) do
	begin
	   read(f,x);
	   write(' ',x:10:1,' ');
	end;
   writeln;
close(f);
end.






