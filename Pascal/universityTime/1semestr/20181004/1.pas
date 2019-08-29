program f;
const
	n = 3;
type vector = array[1..n] of integer;
var	a: vector;
	i: integer; {шаг}
	c: integer; {число которое ищем}
	found: boolean;
begin
	found:= false;
	writeln('Введите ',n, ' чисел');
	for i:=1 to n do read(a[i]);
	writeln('');
	for i:=1 to n do write('  a[',i,']=', a[i],' ');
	{теперь смотрим число}
	writeln('Введите число для поиска');
	read(c);
	for i:=1 to n do 
		if c=a[i] then begin found:=true; break; end;
	if found then writeln('Элемент есть под номером ', i)
	else writeln('Нет такого элемента');
	{теперь меняем отриц числа на модули}
	writeln('Меняю все элементы на модули');
	for i:=1 to n do a[i]:=abs(a[i]);
	for i:=1 to n do write('  a[',i,']=', a[i],' '); {печатаем массив}
end.