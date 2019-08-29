program test;

type list = ^node;
   node = record
	elem: integer;
	next: list;
   end;
var l: list;
   p:	pointer;

begin
   
   new(l);
   l^.elem:=5;
   l^.next:=nil;
   write(ofs(l));
   writeln; writeln;
   
   
end.

