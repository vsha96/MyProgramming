program test;
type //m = array[1..2] of array[1..3] of integer;
m = array[1..2, 1..3] of integer;
var i, j, t: integer;
a: m;
s, st: string;

procedure WriteVectorM(var a: m);
var i: integer;
begin
    for i:=1 to 2 do begin
        for j:=1 to 3 do write(' a[',i,',',j,']=', a[i,j],' ');
        writeln;
    end;
    writeln;
end;

begin
{
	for i:=1 to 2 do
		for j:=1 to 3 do
			a[i,j]:=i+j;
}
	//WriteVectorM(a);
	s:='hello world!';
	writeln(s,' ',ord(s[0]));
	//6.10
	writeln(chr(65),chr(71),chr(69));
	//6.19
	s:=s+' repeeAat hello world';
	writeln(s);
	for i:=1 to (ord(s[0])-1) do
	begin
		if s[i+1]='a' then begin writeln(s[i]); break; end
		else if i=(ord(s[0])-1) then writeln('There is no "a"')
	end;
	//6.20
	writeln('##### ',s[5..-1]);
	s:='the greatest thing is pascal thuck thuckthth';
	s:='ththhtth';
	t:=0;
	//for i:=1 to (ord(s[0])-1) do
	//?????
	//	if s[i..i+1]='th' then t:=succ(t);
	//writeln('6.20) "th" occurs ',t,' times');
	//6.23
	writeln('6.23) введите строку, заканчивая точкой ');
	read(st);
	// через while
	repeat
		if (st='+') or (st='-') then write(st,st) 
		else if (st<'0') and (st>'9') then write(st);
		// шаг по тексту read
	until st='.';
	writeln;
end.




