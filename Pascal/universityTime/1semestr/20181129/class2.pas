program class;
var f: text;
   x: string;
begin
   assign(f,'class2.txt');
   reset(f);
   read(f,x);
   writeln(x[1]);
   close(f);
end.



