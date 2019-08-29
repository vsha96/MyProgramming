program homework;
const
        n = 6;
type vector = array[1..n] of integer;
var     a: vector;
        i,j,k: integer; {шаг}
        c: integer; {число которое ищем}
	t: integer; {for sort}
	mid,r,l: integer; {for search}
        found: boolean;
begin
        writeln('Введите ',n, ' чисел ');
        for i:=1 to n do read(a[i]);
        writeln('');
        {sort}
	for i:=n downto 2 do
		for j:=1 to i-1 do
			if a[j]>a[j+1] then begin
				t:=a[j+1]; a[j+1]:=a[j]; a[j]:=t;
			end;
        for i:=1 to n do write(' a[',i,']=', a[i],' '); {печатаем массив}
        writeln('');
        {теперь ищем эл-т}
	write('Введите число для поиска '); read(c); writeln('');
	l:=1; r:=n; k:=0; {count}
	found:= false;
	while (l<=r) and not found do begin
		mid:=l + (r-l) div 2;
		if a[mid]=c then begin found:=true; end
		else if c<a[mid] then begin r:=mid-1; k:=k+1; end
		else begin l:=mid+1; k:=k+1; end
	end;
	if found then write('Это элемент под номером ',mid,' ;колво сравнений = ',k)
	else write('Нет такого элемента');
	writeln('');
end.

