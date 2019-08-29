program queens;
type mas = array[1..8] of boolean;
   diag = array[1..15] of boolean;
   maindiag= array[-6..8] of boolean;
   pos = array[1..5] of integer;
var a,b: mas;
   c: maindiag;
   d: diag;
   posh, posv: pos; {position horizontal, vertical}
   i: integer;

procedure print(var posh,posv: pos);
   var i: integer;
   begin
	for i:=1 to 5 do
	   write(' ',posh[i],',',posv[i],' ');
	writeln;
   end;

procedure nextposition(f: integer; var posh,posv: pos);
   begin
	if (f<>1) and (posh[f]=8) and (posv[f]=3+f) then
	   begin
		nextposition(f-1,posh,posv);
		if posv[f-1]=8 then 
		   begin
			posv[f]:=1; posh[f]:=posh[f-1]+1;
		   end
		else
		   begin
			posv[f]:=posv[f-1]+1; posh[f]:=posh[f-1];
		   end;
	   end
	else if (posh[1]<>8) and (posv[1]<4) then
	   begin
		if posv[f]=8 then
		   begin
			posv[f]:=1; posh[f]:=posh[f]+1;
		   end
		else
		   begin
			posv[f]:=posv[f]+1;
		   end;
	   end
	else
	   writeln('There is no next position');
   end;

{
########################################
########################################
########################################
}

{
(a –) (b |) (c \) (d /)
}
procedure ferz({var a,b: mas; var c: maindiag; var d: diag;}var posh,posv: pos); //change
   var f,i,j: integer;
	a,b: mas; c: maindiag; d: diag;
	bool: boolean;
   begin
	{cover plates}
	for i:=1 to 8 do
		   begin
			a[i]:=false; b[i]:=false; c[i]:=false; d[i]:=false;
		   end;
		for i:=-6 to 8 do
		   begin
			c[i]:=false;
		   end;
		for i:=1 to 15 do
		   begin
			d[i]:=false;
		   end;
	{/cover plates}
	for f:=1 to 5 do
	   begin
		a[posh[f]]:=true;
		b[posv[f]]:=true;
		c[posv[f]-posh[f]+1]:=true;
		d[posv[f]+posh[f]-1]:=true;
	   end;
//----debug
{
for i:=1 to 8 do
		   begin
			writeln(a[i]:6,b[i]:6,c[i]:6,d[i]:6);
		   end;
	writeln;
}
//----/debug
	{check plates}
	bool:=true; {for search uncovered plate}
	for j:=1 to 8 do
	   begin
		if (bool=true) and (b[j]=false) then {if column isn't covered then check a,c,d}
		   begin
			for i:=1 to 8 do
			   begin
				if (a[i]=false) and (c[j-i+1]=false) and (d[j+i-1]=false) then //change
				   begin
					bool:=false; {here is uncovered plate}
				   end;
			   end;
		   end;
	   end;
	if bool=true then
	   begin
		print(posh,posv);
		nextposition(5,posh,posv);
	   end
	else if bool=false then
	   begin
		nextposition(5,posh,posv);
		{reset a,b,c,d
		for i:=1 to 8 do
		   begin
			a[i]:=false; b[i]:=false; c[i]:=false; d[i]:=false;
		   end;
		for i:=-6 to 8 do
		   begin
			c[i]:=false;
		   end;
		for i:=1 to 15 do
		   begin
			d[i]:=false;
		   end;
		
		ferz(a,b,c,d,posh,posv) recursion}
	   end;
   end;

begin
   for i:=1 to 5 do
	begin
	   posh[i]:=1;
	end;
   for i:=1 to 5 do
	begin
	   posv[i]:=i;
	end;
	
	ferz(posh,posv);
	
end.

