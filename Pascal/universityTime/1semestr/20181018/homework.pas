program homework;
const n = 10;
var i,j: integer;
    c,t: integer;
    s: integer;
    long: uint64;
//5.47
    ends: boolean;
    count: integer;
//5.48
    maxcount: integer;
//6.41
    st: char;
//########
function CountOfDigits(a:int64): integer; var i:integer; begin i:=0; repeat i:=i+1; a:= a div 10; until (a=0); countofdigits:=i; end;
function GiveMeDigitInPosition(a:int64; n:integer): integer; var i: integer; begin for i:=1 to n-1 do begin	a:= a div 10; end; GiveMeDigitInPosition:= a mod 10; end;
//########

//5.51
function palindrome(a:int64): boolean;
var c: integer;
    i: integer;
begin
	c:=countofdigits(a);
	palindrome:=true;
	if a mod 10 = 0 then palindrome:=false
	else begin
		for i:=1 to (c div 2) do
		begin
			if givemedigitinposition(a,i) <> givemedigitinposition(a,(c-i+1)) then 
			begin
				palindrome:=false;
				break;
			end;
		end;
	end;
end;

//5.54
procedure WritePrimeNumbersUpTo(var n:uint64);
var i,j: uint64;
begin
	if (n=2) then write('2');
	if n>2 then write('2, 3, ');
	for i:=5 to n do
	begin
		for j:=2 to (i div 2) do
			if j=(i div 2) then write(i,', ')
			else if (i mod j)=0 then break;
	end;
	writeln;
end;

//5.55
function PerfectNumber(a: uint64): boolean;
var i: uint64;
    s: uint64;
begin
	if a=1 then writeln('Are you kidding? EXIT')
	else begin
		perfectnumber:=false;
		s:=0;
		for i:=1 to (a div 2) do
		begin
			if (a mod i) = 0 then s:=s+i;
		end;
		if s = a then perfectnumber:=true;
	end;
end;

//5.56
//procedure 

//6.41д
function ismultiply5: boolean;
var sum: integer;
begin
	sum:=0; ismultiply5:=false;
	read(st);
	repeat
		case st of
			'1','6','B': sum:=sum+1;
			'2','7','C': sum:=sum+2;
			'3','8','D': sum:=sum+3;
			'4','9','E': sum:=sum+4;
		end;
		read(st);
	until(st='.');
	if (sum mod 5)=0 then ismultiply5:=true
end;



begin
//5.46
	{
	writeln('5.46) Введите последовательность из ',n,' чисел');
	s:=1;
	read(c);
	t:=c;
	for i:=2 to n do
	begin
		read(c);
		if t <> c then s:=s+1;
		t:=c;
	end;
	writeln(s);
	}
//5.47
	{
	writeln('5.47) Введите последовательность из ',n,' чисел');
	read(c);
	t:=c;
	count:=0;
	ends:=false;
	for i:=2 to n do
	begin
		read(c);
		if (t < c) then ends:=false;
		if (t < c) and (ends=false) then begin write(' ',t); count:=count+1; end
		else if (t >= c) and (count>0) then
			begin ends:=true; write(' ',t); writeln; ends:=false; count:=0; end;
		if (ends=false) and (i=n) and (count>0) then write(' ',c);
		t:=c;
	end;
	writeln;
	}
//5.48
	{
	count:=0;
	maxcount:=0;
	writeln('5.48) Введите последовательность из ',n,' чисел');
	for i:=1 to n do
	begin
		read(c);
		if c=0 then count:=count+1;
		if count>maxcount then maxcount:=count;
		if c<>0 then count:=0;
	end;
	writeln('count of zeros in max range = ',maxcount);
	}
//5.51 from now I'm writing procedures or functions
	{
	writeln('5.51) Enter a number ');
	read(long);
	writeln('Is this palindrome? ',palindrome(long));
	}
//5.54
	{
	writeln('5.54) I want to get prime numbers up to ...');
	read(long);
	writeprimenumbersupto(long);
	}
//5.55
	{
	writeln('5.55) Is it perfect number?');
	read(long);
	writeln(perfectnumber(long));
	}
//6.41д
	writeln('6.41) Enter a number ');
	writeln(ismultiply5);
	
end.





