program f;
const n = 5;
type vector = array[1..n] of integer;
var a: vector; s: integer; t: boolean;

procedure ReadVector(var a: vector);
var i: integer;
begin
	writeln('Input array which size ',n,': ');
	for i:=1 to n do begin
		read(a[i]);
	end
end;

procedure WriteVector(a: vector);
var i: integer;
begin
	for i:=1 to n do write(' a[',i,']=', a[i],' ');
	writeln;
end;

//8.20A
procedure SumUntil0(var a: vector;var s: integer);
var i: integer;
begin
i:=1; s:=0;
while (a[i]<>0) and (i<=n) do
	begin
		s:=s+a[i];
		i:=succ(i);
	end
end;
//8.20Б
procedure isvectorsorted(var a:vector; var t: boolean);
var i,f: integer;
begin
	t:=true;
	for i:=2 to n do
	begin
		if a[i-1]>a[i] then t:=false
	end;
end;
//8.20B
procedure simmetry(var a: vector; var t: boolean);
var i,j:integer;
begin
	t:=true; i:=1; j:=n;
	while (a[i]=a[j]) and (i<j) do begin
		i:=succ(i); j:=pred(j);
	end;
	if i<j then t:=false;
end;

//8.29A
procedure ReplaceMaxMin(var a: vector);
var t,max,min,pmax,pmin,i:integer;
begin
	pmax:=1; pmin:=1;
	max:=a[1]; min:=a[1];
	for i:=1 to n do 
		begin
		if max<a[i] then
			begin
				max:=a[i]; pmax:=i;
			end;
		if min>a[i] then
			begin
				min:=a[i]; pmin:=i;
			end;
		end;
	t:=a[pmax]; a[pmax]:=a[pmin]; a[pmin]:=t;
end;
//8.29Б
procedure inversevector(var a:vector);
var i,j,t:integer;
begin
	i:=1; j:=n;
	while (i<j) do
	begin
		t:=a[i]; a[i]:=a[j]; a[j]:=t;
		i:=succ(i); j:=pred(j);
	end;
end;
//8.29Д
procedure moverightvector(var a: vector);
var t,tf,ts,i:integer;
begin
	tf:=a[1];
	for i:=2 to n do
		begin
			ts:=a[i]; t:=ts; a[i]:=tf; tf:=t;
		end;
	a[1]:=ts;
end;
//8.29Г
procedure moveleftvector(var a: vector);
var t,tf,ts,i:integer;
begin
	tf:=a[1];
	for i:=n downto 2 do
		begin
			ts:=a[i]; t:=ts; a[i]:=tf; tf:=t;
		end;
	a[1]:=ts;
end;


begin
	readvector(a);
	writevector(a);
	//sumuntil0(a,s); writeln('8.20A) s = ',s);
	isvectorsorted(a,t); writeln('8.20Б) Is vector sorted? ',t);
	//simmetry(a,t); writeln('8.20B) simmetry = ',t);
	//replacemaxmin(a); writeln('8.29A)'); writevector(a);
	//moverightvector(a); writeln('8.29Д)'); writevector(a);
	//moveleftvector(a); writeln('8.29Г)'); writevector(a);
	//moveleftvector(a); moveleftvector(a); writeln('8.29Е'); writevector(a);
	//inversevector(a); writeln('8.29Б)'); writevector(a);
end.