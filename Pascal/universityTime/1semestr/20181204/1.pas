program class;
var f,res: text;
   x,first: char;
begin
   assign(f,'data.txt');
   assign(res,'result.txt');
   reset(f);
   rewrite(res);
   {вложенность убрать с continue}
   {readln вынести, выполняется один раз}
   while not eof(f) do
	begin
	   if not eoln(f) then
	   begin
		read(f,first);
		if first='#' then
		   begin
			readln(f);
		   end
		else
		   begin
			write(res,first);
			while not eoln(f) do
			   begin
				read(f,x);
				write(res,x);
			   end;
			readln(f);
			writeln(res);
		   end;
	   end
	   else
		begin
		   readln(f);
		   writeln(res);
		end;
	end;
   close(f); close(res);
end.





