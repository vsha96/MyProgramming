unit trees2;

interface
	{Описание типа 'дерево'}
	type tree=^list;
	     list=record
		     left,right:tree;
		     key:integer;
		  end;
	{Процедура создания дерева}
	procedure creature(var t:tree);
	{Процедура добавления элемента n в дерево}
	procedure adding(var t:tree; n:integer);
	{Процедура удаления элемента n из дерева}
	procedure remove(var t:tree; n:integer);
	{Функция поиска элемента n в дереве}
	function find(var t:tree;n:integer):boolean;
	{Функция считающая высоту дерева}
	function hight(t:tree):integer;
	{Процедура очистки дерева}
	procedure dis(var t:tree);
	{Процедура симметрического вывода}
	procedure printsym(t:tree);
	{Процедура прямой печати дерева}
	procedure printst(t:tree);
	{Процедура печати дерева в обратном порядке}
	procedure printinverse(t:tree);
	{Процедура создания дерева Фибониччи}
	procedure fib(var t:tree);

implementation
	{Максимальное из двух элементов}
	function max(a,b:integer):integer;
	begin
		if a>b then
			max:=a
		else
			max:=b;
	end;

	{Функция, считающая высоту дерева}
	function hight(t:tree):integer;
	begin
		if t=nil then
			hight:=0
		else
			hight:=1+max(hight(t^.left),hight(t^.right));
	end;

	{Функция, считающая характеристику дерева}
	function characteristic(t:tree):integer;
	begin
		if t=nil then
			characteristic:=0
		else
			characteristic:=hight(t^.left)-hight(t^.right);
	end;
	{Процедура балансировки}
	procedure balance(var t:tree);
	var i:integer;
	    s:tree;
	begin
		if t<>nil then
		begin
			i:=characteristic(t);
			if i<-1 then			{Случай, когда правое поддерево больше левого}
			begin
				s:=t^.right;
				if characteristic(t^.right)<0 then
				begin
					t^.right:=t^.right^.left;
					s^.left:=t;
					t:=s;
				end
				else 
				begin
					t^.right:=t^.right^.left^.left;
					s^.left^.left:=t;
					t:=s^.left;
					s^.left:=t^.right;
					t^.right:=s;
				end;
			end	
			else if i>1 then		{Случай, когда левое поддерево больше правого}
			begin
				s:=t^.left;
				if characteristic(t^.left)>0 then
				begin
					t^.left:=t^.left^.right;
					s^.right:=t;
					t:=s;
				end
				else
				begin
					t^.left:=t^.left^.right^.right;
					s^.right^.right:=t;
					t:=s^.right;
					s^.right:=t^.left;
					t^.left:=s;
				end;
			end;
			balance(t^.right);
			balance(t^.left);
		end;
	end;

	{Процедура добавления элемента n в дерево}
	procedure adding(var t:tree;n:integer);
	begin
		if t=nil then
		begin
			new(t);
			t^.left:=nil;
			t^.right:=nil;
			t^.key:=n;
		end
		else if t^.key<>n then
		begin
			if n<t^.key then
				adding(t^.left,n)
			else
				adding(t^.right,n);
			balance(t);
		end
		else
		begin
			writeln;
			writeln('Вводите различные значения!');
		end;
	end;

	{Процедура создания дерева}
	procedure creature(var t:tree);
	var i:integer;
	begin
		writeln('Введите элементы дерева в строчку (все элементы должны быть различными):');
		if eoln then
			t:=nil 
		else 
		       	while not eoln do 
			begin 
				read(i); 
				adding(t,i);
			end;
	end;

	{Функция поиска элемента n в дереве}
	function find(var t:tree;n:integer):boolean;
	begin
		if t=nil then
			find:=false
		else if t^.key>n then
			find:=find(t^.left,n)
		else if t^.key<n then
			find:=find(t^.right,n)
		else
			find:=true;
	end;

	{Процедура очистки всего дерева}
	procedure dis(var t:tree);
	begin
		if t<>nil then
		begin
			if t^.left<>nil then
				dis(t^.left);
			if t^.right<>nil then
				dis(t^.right);
			dispose(t);
		end;
	end;

	{Удаление элемента n из дерева}
	procedure remove(var t:tree;n:integer);
	var s,parent,y:tree; {удаляемый, предок удаляемого, заменяющий удаляемый узлы}

	function descent(s:tree):tree;{Вспомогательная функция для поиска заменяющего узла и его предка}
	var y,parent2:tree; {заменяющий удаляемый, предок заменяющего}
	begin
		y:=s^.right;
		if y^.left=nil then
			y^.left:=s^.left
		else
		begin
			repeat
				parent2:=y;
				y:=y^.left;
			until y^.left=nil;
			parent2^.left:=y^.right;
			y^.right:=s^.right;
		end;
		descent:=y;
	end;

	function search(t:tree;n:integer;var s,parent:tree):boolean;{Функция поиска узла с элементом n и предка этого узла}
	begin
		s:=t;
		while s<>nil do 
		begin
			if n=s^.key then
			begin
				search:=true;
				exit;
			end;
			parent:=s;
			if n<s^.key then
				s:=s^.left
			else
				s:=s^.right;
		end;
		search:=false;
	end;

	begin
		if not search(t,n,s,parent) then
		begin
			writeln('Такого элемента в дереве нет.');
			exit;
		end;
		if s^.left=nil then
			y:=s^.right
		else if s^.right=nil then
			y:=s^.left
		else
			y:=descent(s);
		if s=t then t:=y
		else
		begin
			if n<parent^.key then
				parent^.left:=y
			else 
				parent^.right:=y;
		end;
		dispose(s);
		balance(t);
	end;

	{Симметричная печать дерева}
	procedure printsym(t:tree);
	begin
		if t<>nil then
		begin
			printsym(t^.left);
			writeln(t^.key);
			printsym(t^.right);
		end;
	end;

	{Прямая печать дерева}
	procedure printst(t:tree);
	begin
		if t<>nil then
		begin
			writeln(t^.key);
			printst(t^.left);
			printst(t^.right);
		end;
	end;

	{Печать дерева в обратном порядке}
	procedure printinverse(t:tree);
	begin
		if t<>nil then
		begin
			printinverse(t^.left);
			printinverse(t^.right);
			writeln(t^.key);
		end;
	end;

	{Процедура создания дерева Фибоначчи, дерево изначально должно быть пустым}
	procedure fib(var t:tree);
	var n,i:integer;

	procedure create(k:integer; var t:tree);
	begin
		if k=0 then
		t:=nil
	else
		if k=1 then
		begin
			new(t);
			t^.left:=nil;
			t^.right:=nil;
		end
		else
		begin
			new(t);
			create(k-1, t^.left);
			create(k-2, t^.right);
		end;
	end;

	procedure fill(var t:tree; var i:integer);
	begin
		if t<>nil then
		begin
			fill(t^.left, i);
			t^.key:=i;
			inc(i);
			fill(t^.right, i);
		end;
	end;

	begin
		if t=nil then
		begin	
			writeln('Введите порядок числа Фибоначчи (n>=0):');
			read(n);
			create(n,t);
			i:=1;
			fill(t,i);
			if t=nil then
				writeln('Число Фибоначчи:', 1)
			else
				writeln('Число Фибоначчи:', t^.key);
		end
		else
			writeln('Перед использованием этой процедуры очистите дерево (его значение должно быть nil).');
	end;
end.
