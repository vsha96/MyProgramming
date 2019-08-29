program first;
uses bi_list;
var f: text; x: char;
   l,p: ls;
   m,c1,c2: integer; {count of steps, of comparisons before, -||- -||- after}
   t: integer;
   digit, flag: boolean; {for brackets}
{!убрать глобальную переменную!}
procedure move(t: integer); {counts movement}
   begin
	m:=m+t;
   end;

begin
   assign(f,'data.txt');
   reset(f); listinit(l);
   
   while not eof(f) do
	begin
	   while not eoln(f) do
		begin
		   read(f,x);
		   listaddlast(l,x);
		end;
	   c1:=listpower(l); {c1}
	{now we change our list}
	   {remove >1 spaces}
	   p:=searchel(l,' ',t); move(t);
	   while p<>nil do
		begin
		   if p^.next<>nil then
			begin
			   while p^.next^.elem=' ' do
				begin
				   delitem(p^.next,' '); {more m}
				   move(1);
				   if p^.next=nil then break;
				end;
			   if p<>nil then
				p:=searchel(p^.next,' ',t); move(t);
			end
		   else p:=p^.next;
		end;
	   {/remove >1 spaces}
	   {place digits in brackets}
	   p:=l; flag:=false;
	   while p<>nil do
		begin
		   digit:= p^.elem in ['0'..'9'];
		   if digit and not(flag) then
			begin
				insertbefore(p,'{'); flag:=true;
			end;
		   if digit and flag then
			begin
			   if p^.next<>nil then
				begin
				   if p^.next^.elem in ['0'..'9'] then
					begin
					   p:=p^.next; continue;
					end
				   else begin insertafter(p,'}'); flag:=false; end;
				end
			   else begin insertafter(p,'}'); flag:=false; end;
			end;
		   p:=p^.next; move(1);
		end;
	   {/place digits in brackets}
	{/now we change our list}
	   c2:=listpower(l); {c2}
	   readln(f);
	   printlist(l); write('movement = ',m,'; count1 = ',c1,'; count2 = ',c2,';'); writeln;
	   dellist(l); listinit(l); m:=0;
	end;
   close(f);
end.





