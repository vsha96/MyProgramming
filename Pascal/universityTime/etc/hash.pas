unit hash;

interface

const 
		{Размер ХЭШ-таблицы} {МОЖНО МЕНЯТЬ}
		n = 26; 

type
		{Указатель на элемент таблицы}
		link = ^htElem;
		
		{Тип элементов}
		valueType = string;
		
		{элементы ХЭШ-таблицы}
		htElem = record 
		{МОЖНО ДОБАВИТЬ ДРУГИЕ ПОЛЯ: может понадобиться менять htoutput для вывода содержимого}
			value: valueType;
			next: link;
		end;
		
		{ХЭШ-таблица}
		hashTable = array[0..n - 1] of link;
		
           {Инициализация ХЭШ-Таблицы}
           procedure htInit(var ht: hashTable);

           {Добавление одного элемента}
           procedure htAdd(var ht: hashTable; A: valueType);

           {Заполнение таблицы (несколько элементов)}
           procedure htFill(var ht: hashTable);

           {Удаляет элемент А}
           procedure htDelOne(var ht: hashTable; A: valueType);

           {Находится ли A в таблице?}
           function htInHashTable(var ht: hashTable; A: valueType): boolean;

           {Дать ссылку на A}
           function htFindElement(var ht: hashTable; A: valueType): link;

           {Очистка таблицы и Освобождение памяти}
           procedure htFree(var ht: hashTable);

           {Сколько элементов в хэш таблице?}
           function htPower(var ht: hashTable): integer;

           {Вывод всех ключей (value) таблицы}
           procedure htOutput(var ht: hashTable);



implementation

	{Инициализация ХЭШ-Таблицы}
procedure htInit(var ht : hashTable);
	var
		i : integer;
	begin
		for i := 0 to n - 1 do
			ht[i] := nil
	end;
	

	{Локальная процедура для очистки памяти (не идет в интерфейс)}
procedure Free(L : link);
	begin
		if L <> nil then begin
			if L^.next <> nil then Free(L^.next);
			dispose(L);
		end;
	end;
	
	
	{Очистка таблицы и Освобождение памяти}
procedure htFree(var ht: hashTable);
	var
		i : integer;
	begin
		for i := 0 to n - 1 do begin
			Free(ht[i]);
		end; 
		htInit(ht);
	end;
	

	{Добавление одного элемента} 
procedure htAdd(var ht: hashTable; A: valueType); 
	var 
		l, j, p : link; 
		t : integer; 
	begin 
		t := ord(a[1])-ord('a'); 
		l := ht[t]; 
		p := l; 
		if l = nil then begin 
			new(ht[t]); 
			ht[t]^.value := A; 
			ht[t]^.next := nil; 
		end 
		else if l^.value > A then begin 
			new(j); 
			j^.value := A; 
			j^.next := l; 
			ht[t] := j; 
		end 
		else begin 
			while (l^.next <> nil) and (l^.value < A) do
				l := l^.next; 
			if (l^.next = nil) and (l^.value < A) then begin 
				new(l^.next); 
				l^.next^.value := A; 
				l^.next^.next := nil 
			end 
			else begin 
				while p^.next^.value < A do 
					p := p^.next; 
				new(j); 
				j^.value := A; 
				j^.next := l; 
				p^.next := j; 
			end 
		end; 
	end;

	{Заполнение таблицы (несколько элементов)}
procedure htFill(var ht: hashTable);
	var
 		A : valueType;
	begin
		while not eoln do begin
			read(A);
			htAdd(ht, A);
		end;
	end;
	
	
	{Локальная процедура для вывода (не идет в интерфейс)}
procedure outputLine(L : link);
	begin
		if L <> nil then begin
			write(' ', L^.value);
			outputLine(L^.next);
		end;
	end;
	

	{Вывод всех элементов}	
procedure htOutput(var ht: hashTable);
	var 
		i : integer;
	begin
		writeln;
		writeln('#########################');
		writeln('Output of Hash Table');
		writeln('Size of Hash Table is :   ', n);
		for i:=0 to n-1 do begin
			write('[', i, ']');
			outputLine(ht[i]);
			writeln;
			writeln;
		end; 
		writeln('#########################');
		writeln;
	end;	
	
	
	
	{Находится ли A в таблице?}	
function htInHashTable(var ht: hashTable; A: valueType): boolean;
	var
		L: link;
		f: boolean;
	begin
		L := ht[ord(a[1])-ord('a')];
		f := False;
		while L <> nil do begin
			if L^.value = A then begin
				f := True;
				break;
			end
			else if L^.value > A then 
				break;
			L := L^.next;
		end;
		htInHashTable := f;
	end;
	
	{Дать ссылку на A}
function htFindElement(var ht: hashTable; A: valueType): link;
	var
		 l, result: link;
	begin
		l := ht[ord(a[1])-ord('a')];
		result := nil;
		while l <> nil do begin
			if l^.value = A then begin
				result := l;
				break;
			end
			else if l^.value > A then 
				break;
			l := l^.next;
		end;
		htFindElement := result;		
	end;

	
	{Удаляет элемент А из ХТ}
   
procedure htDelOne(var ht: hashtable; A: ValueType); 
	var 
		l, j : link;
		t : integer;
	begin
		t := ord(a[1])-ord('a');
		l := ht[t];
		if ht[t]^.value = A then begin 
			j := ht[t]^.next; 
			dispose(ht[t]); 
			ht[t] := j 
		end 
		else begin 
			while l^.next^.value <> A do 
				l := l^.next; 
			j := l^.next^.next; 
			dispose(l^.next); 
			l^.next := j 
		end 
	end; 

	{Показывает количество элементов в Хэш-таблице}
function htPower(var HT: hashtable): integer;
	var
		L: Link;
		count, k: integer;
	begin
		K := 0;
		count := 0;
		while (k < n) do begin     {Запускаем цикл,который проходит по каждой ячейке ХТ}
			L := ht[k mod n];
			k := k + 1;
			while L <> nil do begin {Запускаем цикл,который проходит "вглубь" каждой ячейки и подсчитываем их количество}
				count := count + 1;
				L := L^.next;
			end;
		end;
		htPower := count;
	end;

end.