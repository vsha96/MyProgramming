program main;
   function log():boolean;
	var c:char; b: boolean;
	begin
	   read(c);
	   if c='n' then
		begin
		   read(c); read(c); read(c); {n ot(}
		   log:= not(log());
		   read(c); {)}
		end
	   else if c='a' then
		begin
		   read(c); read(c); read(c); {a nd(}
		   b:=log();
		   read(c); {,}
		   {цикл до скобки}
		   log:=b and log();
		   read(c); {)}
		end
	   else if c='o' then
		begin
		   read(c); read(c); {o r(}
		   b:=log();
		   read(c); {,}
		   log:=b or log();
		   read(c); {)}
		end
	   else if c='t' then
		begin
		   read(c); read(c); read(c); {t rue}
		   log:= true;
		end
	   else if c='f' then
		begin
		   read(c); read(c); read(c); read(c); {f alse}
		   log:= false;
		end;
	end;

begin
   writeln(log);
end.


