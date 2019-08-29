unit bi_list;
interface
type ls=^node;
node=record
  elem: char;
  next: ls;
  pred: ls;
end;
procedure createlist (var p:ls);
procedure printlist(l:ls);
procedure insertAfter(var p:ls; a:char);
procedure insertBefore(var p:ls; a:char);
function searchel(l:ls;a:char;{for task}var steps:integer):ls;
procedure delitem(var p: ls; item : char);
procedure delList(var list:ls);
{########## edited by vsha96}
procedure listinit(var l:ls);
procedure listaddlast(var l:ls; a:char); {добавить элемент в конец}
function listpower(l:ls):integer; {колво элементов списка}
{ниже процедуры не понадобились есть insertafter и before, их хватает для решения task4}
//procedure listAddAfter(var l:ls; p:ls); {добавление ячейки в список по ссылке до l}
//procedure listAddBefore(var l:ls; p:ls); {после l}
{/#########}

implementation
procedure createlist (var p:ls);
var a:char;l:ls;
begin
  if not eoln then
    begin
      read(a);
      new(p);
      p^.elem:=a;
      p^.pred:=nil;
    end;
  l:=p;
  while not eoln do 
    begin
      read(a);
      new(l^.next);
      l^.next^.elem:=a;
      l^.next^.pred:=l;
      l:=l^.next;
    end;
  readln();
end;

{############## edited by vsha96}
procedure listinit(var l:ls);
   begin
	dellist(l);
	l:=nil;
   end;
procedure listaddlast(var l:ls; a:char);
   var p: ls;
   begin
	p:=l;
	if p=nil then
	   begin
		new(l);
		l^.elem:=a;
		l^.pred:=nil; l^.next:=nil;
	   end
	else	if p^.next=nil then
		   begin
			new(p^.next);
			p^.next^.elem:=a;
			p^.next^.pred:=p; p^.next^.next:=nil;
		   end
		else  listaddlast(p^.next,a);
   end;
function listpower(l:ls):integer;
begin
   listpower:=0;
   while l<>nil do
	begin
	listpower:=listpower+1;
	l:=l^.next;
	end;
end;
{/#############}

procedure printlist(l:ls);
begin
  while l<>nil do
    begin
      Write(l^.elem);
      l:=l^.next;
  end;
  writeln;
end;

procedure insertAfter(var p:ls; a:char);
{принимает два аргумента:
1) указатель на узел, после которого происходит добавление
2) данные для добавляемого узла}
var
 newls:ls;
begin
 if p<>nil then 
  begin 
   new(newls); {создаем узел добавляемого элемента}
   newls^.elem:=a; {заполняем его поле данных}
   newls^.pred:=p; {присваиваем указателю pred добавляемого узла ссылку на предыдущий узел}
   newls^.next:=p^.next; {присваиваем указателю next добавляемого узла ссылку на следующий узел}
   p^.next:=newls; {меняем указатель next предыдущего узла на добвляемый узел}
   if newls^.next<>nil then newls^.next^.pred:=newls; {меняем указатель pred следующего узла на добавляемый узел}
  end
 else {если аргумент - пустая ссылка, то создает корневой узел списка}
  begin 
   new(p);
   p^.next:=nil;  
   p^.pred:=nil;
   p^.elem:=a
  end
end;

procedure insertBefore(var p:ls; a:char); 
{принимает два аргумента:
1) указатель на узел, перед которым происходит добавление
2) данные для добавляеиого узла}
var
 newls:ls;
 f:boolean;
begin
 if p<>nil then 
  begin 
   {vsha96} f:=false; {/: флаг}
   new(newls); {создаем узел добавляемого элемента}
   newls^.elem:=a; {заполняем его поле данных}
   newls^.pred:=p^.pred; {присваиваем указателю pred добавляемого узла ссылку на предыдущий узел}
   newls^.next:=p; {присваиваем указателю next добавляемого узла ссылку на следующий узел}
   {vsha96} if p^.pred=nil then f:=true; {/:если это первое звено -> нужно менять указатель всего списка!}
   p^.pred:=newls; {меняем указатель pred следующего узла на добавляемый узел}
   {vsha96} if f then p:=newls; {/:меняем указатель всего списка}
   if newls^.pred<>nil then {если добавляемый узел не первый в списке,}
   newls^.pred^.next:=newls; {меняем указатель next предыдущего узла на добавляемый узел}
  end
 else {если аргумент - пустая ссылка, то создает корневой узел списка}
  begin 
   new(p);
   p^.next:=nil;  
   p^.pred:=nil;
   p^.elem:=a
  end
end;

function searchel(l:ls;a:char;{for task}var steps:integer):ls;
begin
   steps:=0;
  searchel:=nil;
  while l<>nil do
      if l^.elem=a then 
        begin
          searchel:=l;
          break;
        end
      else begin
        l:=l^.next; steps:=steps+1; end;
end;

procedure delitem(var p: ls; item : char);
var n, start : ls;
begin
  start:=p;
  if start = nil then writeln('List is epmty!')
  else
    while (start <> nil) do
    begin
      if(start^.elem = item) then
      begin
        if (start^.pred = nil) then begin { if first element }
          n:= start;
          p:=p^.next;
          start:=start^.next;
          start^.pred:= nil;
          dispose(n);
        end else
        if (start^.next = nil) then begin { if last elemenet }          
          start^.pred^.next:= nil;
          dispose(start);
        end else
        begin
         start^.pred^.next:=start^.next;
         start^.next^.pred:=start^.pred;
         dispose(start);
        end;
      end else start:=start^.next;
    end;
end;

procedure delList(var list:ls);
var
  p:ls;
begin
  p:=list;
  while(list<>nil) do
  begin
    list:=p^.next;
    dispose(p);
    p:=list
  end
end;
end.