program class;
type rfile = file of real;
var f: rfile;
   x: real;

function negsum(var f: rfile): real;
   var x: real;
   begin
	reset(f);
	negsum:=0;
	while not eof(f) do
	   begin
		read(f,x);
		if x<0 then
		   negsum:=negsum+x;
	   end;
   end;

begin
   assign(f,'data.txt');
   rewrite(f);
   while not eoln() do
	begin
	   read(x);
	   write(f,x);
	end;
   reset(f);
   while not eof(f) do
	begin
	   read(f,x);
	   write(' ',x:10:1,' ');
	end;
   writeln;
   write(negsum(f):5:3);
   writeln;
   close(f);
end.