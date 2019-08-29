program test;

type	list1=^node1;
	node1 = record
	   elem: integer;
	   next: list1;
	   end;
	list2=^node2;
	node2 = record
	   elem: integer;
	   next: list2;
	   prev: list2;
	   end;
	t = (a,b,c);
function max(): integer;
	var k,c:integer;
	begin
		read(c);
		if c<>0 then
		begin
			k:=max();
			if c > k then
				max:= c
			else max:= k;
		end;
	end;

function dig7(n: integer): integer;
   begin
	if (n<>1) and ((n mod 7) <> 0) then
	   dig7:= -1
	else 
	   if n = 1 then
		dig7:= 0
	   else
		dig7:=1+dig7(n div 7);
   end;

begin
	{
	writeln(round(-3.5));
	writeln(trunc(3.5));
	}
	writeln(pred(ord(a)));
	
	
	
end.