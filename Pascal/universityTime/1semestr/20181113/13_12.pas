program homework;
type raz = record
   chisl: integer;
   znam: 1..maxint;
   end;
   massiv = array[1..20] of raz;
var a,b,c,m: raz;
   x: massiv;

function ravno(var a,b: raz): boolean;
   begin 
	ravno:=false;
	if (a.chisl=0) and (b.chisl=0) then ravno:=true
	else if (b.chisl<>0) and ((a.chisl*b.znam)/(a.znam*b.chisl)=1) then ravno:=true;
   end;
begin
   writeln('a = '); readln(a.chisl,a.znam);
   writeln('b = '); readln(b.chisl,b.znam);
   writeln('ravno = ',ravno(a,b));
end.
