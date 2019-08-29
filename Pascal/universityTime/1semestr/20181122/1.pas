program first;
type list=^node;
   node = record
	elem: integer;
	next: list;
   end;
var l: list;
   k: integer;

procedure buildlist2(var l: list; n,k: integer);
   begin
	if n=0 then
	   l:=nil;
	if n<>0 then
	   begin
		new(l);
		case n of
		   3: l^.elem:=k;
		   2: l^.elem:=k+10;
		   1: l^.elem:=k+100;
		end;
		buildlist2(l^.next,n-1,k);
	   end;
   end;

{####}
procedure putlist(var l: list; k: integer);
   var p: node;
   begin
	p.elem:=k; p.next:=l;
   end;
{####}

{
procedure buildlist3(var l: list);
   var k: integer;
	p: list;
   begin
	new(l);
	l:=nil;
	while not eoln() do
	   begin
		read(k);
		if (k mod 2)=0 then
		begin
		   
		   putlist(p,k);
		end;
	   end;
   end;

{
function sum(var l: list): real;
   begin
	
   end;
}
procedure writelist(var l:list);
   begin
	if l<>nil then
	   begin
		write(l^.elem,' ');
		writelist(l^.next);
	   end;
	if l=nil then
	   begin
		writeln; writeln;
	   end;
   end;
procedure deletelist(var l:list);
   var t: list;
   begin
	if l<>nil then
	   begin
		t:=l^.next;
		dispose(l);
		deletelist(t);
	   end;
   end;

begin
   {
   write('2) input k ');
   read(k);
   buildlist2(l,3,k);
   writelist(l);
   deletelist(l);
   }
   {
   writeln('input sequence ');
   buildlist3(l);
   writelist(l);
   deletelist(l);
   }
   buildlist3(l);
   writelist(l);
   deletelist(l);
   //writeln('the arithmetic mean = ',sum(l));
end.



