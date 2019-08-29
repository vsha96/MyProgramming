program quicksort;
const n = 10;
type vector = array[1..n] of integer;
var a: vector;
    i: integer
//------
procedure WriteVector(a: vector);
var i: integer;
begin
    for i:=1 to n do write(' a[',i,']=', a[i],' ');
    writeln;
end;
procedure ReadVector(var a: vector);
var i: integer;
begin
    writeln('Input array which size ',n,': ');
    for i:=1 to n do begin
	read(a[i]);
    end
end;
//swap is also useful
procedure swap(var a,b: integer); var c: integer; begin c:=b; b:=a; a:=c; end.
//partition will help quicksort
procedure partition(var a:vector; l,r:integer; var q:integer);
begin
	
end;

//quicksort
procedure quicksort(var a: vector);
var i,j,l,r: integer;
begin
	
end;
//------
begin
	
	
	
end.