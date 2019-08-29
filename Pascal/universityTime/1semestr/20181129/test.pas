program scp;
const n = 8; var m: array[1..n] of string; i: integer; a,b,c,d,e,f,g: char;
begin
a:=chr(39); b:=chr(109); c:=chr(91); d:=chr(93); e:=chr(58); f:=chr(61); g:=chr(59);
m[1]:='program scp;';
m[2]:='const n = 8; var m: array[1..n] of string; i: integer; a,b,c,d,e,f,g: char;';
m[3]:='begin';
m[4]:='a:=chr(39); b:=chr(109); c:=chr(91); d:=chr(93); e:=chr(58); f:=chr(61); g:=chr(59);';
m[5]:='for i:=1 to 4 do writeln(m[i]);';
m[6]:='for i:=1 to 8 do writeln(b,c,i,d,e,f,a,m[i],a,g);';
m[7]:='for i:=5 to n do writeln(m[i]);';
m[8]:='end.';
for i:=1 to 4 do writeln(m[i]);
for i:=1 to 8 do writeln(b,c,i,d,e,f,a,m[i],a,g);
for i:=5 to n do writeln(m[i]);
end.
