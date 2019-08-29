unit hashTableLibrary;

interface

const 
		{Размер ХЭШ-таблицы} {МОЖНО МЕНЯТЬ}
		n = 5; 

type
		{Указатель на элемент таблицы}
		link = ^htElem;
		
		{Тип элементов}
		valueType = integer;
		
		{элементы ХЭШ-таблицы}
		htElem = record 
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

   {Вывод всех элементов}
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
		l, J : link;
		t : integer;
		
	begin
		t := a mod n;
		l := ht[t];
		if ht[t] = nil then begin
				new(ht[t]);
				ht[t]^.value := A;
				ht[t]^.next := nil;
				
		end
		
		else begin
			while true do begin
				if  l^.next = nil then begin
					new(l^.next);
					l^.next^.value := A;
					l^.next^.next := nil;
					break;
				end
				else begin
					if l^.next^.value > A then begin
						new(J);
						J^.value := A;
						J^.next := l^.next;
						l^.next := J;
						break;
					end
					else l := l^.next;
				end;
			end;	
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
		end; 
		writeln('#########################');
		writeln;
	end;	
	
	
	
	{Находится ли A в таблице?}	
function htInHashTable(var ht: hashTable; A: valueType): boolean;
	var
		l: link;
		f: boolean;
	begin
		l := ht[a mod n];
		f := False;
		while l <> nil do begin
			if l^.value = A then begin
				f := True;
				break;
			end
			else if l^.value > A then break;
			l:=l^.next;
		end;
		htInHashTable := f;
	end;
	
	{Дать ссылку на A}
function htFindElement(var ht: hashTable; A: valueType): link;
	var
		 l, result: link;
	begin
		l := ht[a mod n];
		result := nil;
		while l <> nil do begin
			if l^.value = A then begin
				result := l;
				break;
			end
			else if l^.value > A then break
		end;
		htFindElement := result;		
	end;
	
	
	{Удаляет элемент А из ХТ}
procedure htDelOne(var ht: hashtable; A: ValueType);
   var p,t: Link; k: integer;
   begin
	k:= A mod n; {ТУТ ДОЛЖНА БЫТЬ ФУНКЦИЯ!!! h1(a)}
	p:=ht[k]; t:=p;
	if p<>nil then
	   begin
		if (t^.next=nil) and (t^.value=A) then
		   begin
			ht[k]:=nil; dispose(t); t:=nil; p:=nil;
		   end
		else if (t^.next<>nil) and (t^.value=A) then
		   begin
			ht[k]:=ht[k]^.next; dispose(t); t:=nil; p:=nil;
		   end
		else if t^.next<>nil then
		   begin
			t:=t^.next;
			while t<>nil do
			   begin
				if (t^.value = A) then
				   if t^.next<>nil then
					begin
					   p^.next:=t^.next; dispose(t); t:=nil;
					end
				   else
					begin
					   p^.next:=nil; dispose(t); t:=nil;
					end
				else
				   begin
					p:=p^.next; t:=t^.next;
				   end;
			   end;
		   end;
	   end;
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
