program first;
type list=^node;
   node = record
	elem: integer;
	next: list;
   end;
var l: list;
   i,k,m: integer;

{##################################################}
procedure putlist(var l: list; k: integer);
   var p: list;
   begin
	new(p);
	p^.elem:=k; p^.next:=l;
	l:=p;
   end;
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
	   end
   end;
procedure buildlist(var l: list);
   var k: integer;
   begin
	while not eoln() do
	   begin
		read(k);
		putlist(l,k);
	   end;
   end;
{##################################################}

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

procedure buildlist3(var l: list);
   var k: integer;
   begin
	while not eoln() do
	   begin
		read(k);
		if not odd(k) then
		   begin
			putlist(l,k);
		   end;
	   end;
   end;

function averagesum(var l: list): real;
   var s,n: integer;
	p: list;
   begin
	s:=0; n:=0;
	p:=l;
	if l=nil then 
	   begin
		writeln('!there are no elements!');
		averagesum:=0;
	   end
	else
	   begin
		while p<>nil do
		   begin
			s:=s+p^.elem;
			n:=n+1;
			p:=p^.next;
		   end;
		averagesum:=s/n;
	   end;
   end;

procedure listswapfl(var l: list); {swaps first and last elements of list}
var first,last: list;
   t1,t2: list;
begin
   if (l<>nil) and (l^.next<>nil) and (l^.next^.next=nil) then
	begin
	   first:=l; last:=l^.next;
	   l:=last; last^.next:=first; first^.next:=nil;
	end
   else if (l<>nil) and (l^.next<>nil) then
   begin
	first:=l; last:=l; t1:=l; t2:=l;
	while last^.next<>nil do
	   begin
		t2:=last;
		last:=last^.next;
		t1:=l^.next;
	   end;
	first^.next:=nil; t2^.next:=first;
	l:=last; last^.next:=t1;
   end;
end;

procedure listdouble(var l: list);
var p,t:list;
begin
   p:=l;
   while(p<>nil) do
	begin
	   new(t);
	   t^.next:=p^.next; t^.elem:=p^.elem;
	   p^.next:=t;
	   p:=t^.next;
	end;
end;

function listlink(var l: list; i: integer): list;
   var t: integer;
	p:list;
   begin
	if l=nil then begin
	   writeln('!there are no elements!'); listlink:=nil;
	end
	else begin
	   p:=l; t:=1;
	   while (p<>nil) and (t<=i) do
		begin
		   p:=p^.next; t:=t+1;
		end;
	   if t=i then listlink:=p
	   else listlink:=nil;
	end;
   end;

procedure listchange(var l: list; k,m:integer);
   var p: list;
   begin
	p:=l;
	while p<>nil do
	   begin
		if p^.elem=k then p^.elem:=m;
		p:=p^.next;
	   end;
   end;

begin
   {task 2}
   {
   write('2) input k ');
   read(k);
   buildlist2(l,3,k);
   writelist(l);
   deletelist(l);
   }
   
   {task 3*}
   
   writeln('input sequence ');
   buildlist3(l);
   writelist(l);
   //deletelist(l);
   
   
   {task 5}
   
   //buildlist(l);
   //writelist(l);
   writeln('the arithmetic mean = ',averagesum(l):5:4);
   //deletelist(l);
   
   
   {task 6}
   
   //buildlist(l);
   //writelist(l);
   writeln('task 6: list swap');
   listswapfl(l);
   writelist(l);
   //deletelist(l);
   
   
   {task 7}
   
   //buildlist(l);
   //writelist(l);
   writeln('task 7: double elements');
   writeln('there is doubled list '); listdouble(l);
   writelist(l);
   //deletelist(l);
   
   
   {task 8}
   
   //buildlist(l);
   writeln('which link of elemnt do you need? i = '); read(i); //?делаю read в буфер, watch build (тоже из буфера строиться) нужно прописать readln?
   if listlink(l,i)<>nil then writeln('element = ',listlink(l,i)^.elem)
   else writeln('nil');
   //deletelist(l);
   
   
   {task 9}
   
   //buildlist(l); writelist(l);
   write('task 9: in list change elements = '); read(k); write(' to '); read(m);
   listchange(l,k,m);
   writeln('changed list ');
   writelist(l);
   deletelist(l);
   
end.



