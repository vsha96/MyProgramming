% Shulygin Ivan
% CMC MSU 425

/*
перед каждым предикатом есть описание, с обозначениями

==ОБОЗНАЧЕНИЯ==
D  - детерминированный вывод 
ND - недетерминированный 

пример: ii D - <описание_работы_предиката>
*/



/* 9) sort(L1,L2) (вставками)
ii D - проверка: первый список это отсортированный второй
	списки могут быть разной длины
io D - сортировка L1, результат L2
*/
msort(L1,L2):-in_sort(L1,L2,[]).
in_sort([],L2,L2).
in_sort([X|T1],L2,[]):-in_sort(T1,L2,[X]).
in_sort([X|T1],L2,[Y|T2]):-
	X > Y,!, in_sort([X],LT,T2), in_sort(T1,L2,[Y|LT])
	;in_sort(T1,L2,[X,Y|T2]).

/* 10) subset(M1,M2)
ii D - проверка подмножества
*/
msubset([],_).
msubset([E|T],M2):-member(E,M2),msubset(T,M2).
/*
oi ND - поиск подмножества M2
*/
msubset2([],[]).
msubset2([E|T1],[E|T2]):-msubset2(T1,T2).
msubset2(T1,[_|T2]):-msubset2(T1,T2).

/* 11) union(M1,M2,M3)
iii D - является ли M3 объединением M1 и M2
iio D - объединяет мно-ва М1 и М2
ioi D - в М2 повтор результата М3 
	(т.е. такое использование возможно, но нет смысла)
*/
munion(M1,M2,M3):-in_munion(M1,M2,M),permutation(M,M3),!.
in_munion([],M2,M2).
in_munion(M1,[],M1):-!.
in_munion([X|T1],M2,M3):-member(X,M2),!,in_munion(T1,M2,M3).
in_munion([X|T1],M2,[X|M3]):-in_munion(T1,M2,M3).






/* ================= */
/* ===== ГРАФЫ ===== */
/* ================= */
edge(a,b,10).
edge(c,b,20).
edge(c,d,5).
edge(e,d,5).
edge(e,f,10).
edge(e,b,5).
edge(a,f,25).

/* предикат неориентированности графа */
medge(X,Y,Z):-edge(X,Y,Z);edge(Y,X,Z).

/* 16) path(X,Y,L) - путь из одной вершины в другую
iii D - есть ли путь, заданный L, между X и Y
iio ND - выводит все возможные пути
ioi D - берет последнюю вершину в L (нет смысла)
ioo ND - все возможные пути из вершины X
oii D - берет первую вершину в L (нет смысла)
oio ND - все возможные пути в вершину Y
ooi D - берет первую и последнюю вершину в L (нет смысла)
ooo ND - все возможные пути из любых вершин
*/
path(X,Y,Route):-costpath(X,Y,Route,_).

/* costpath(X,Y,L,C) - путь со стоимостью
работа такая же как в (16), добавляется стоимость пути
*/
costpath(S,E,Route,Cost):-
	ext_path(S,E,Route,[E],Cost).
ext_path(S,S,L,L,0).
ext_path(S,E,L,Lp,Cost):-
	medge(E,T,Ct),\+ member(T,Lp),ext_path(S,T,L,[T|Lp],Ctn),
	Cost is Ct+Ctn.

/* 17) min_path(S,E,Cost*List)
	- минимальный по стоимости путь между S и E
		! здесь в третьем аргументе добавлена стоимость
iii D - минимален ли заданный путь между S и E
	(! может также выдавать false, если пути нет такого)
iio ND - все минимальные пути из S в E
*/
min_path(S,E,Cost*Path):-
	findall(C*P,costpath(S,E,P,C),L),
	ext_mincost(L,Cost),
	member(Cost*Path,L).
ext_mincost([C*_],C):-!.
ext_mincost([C*_|T],MC):-ext_mincost(T,MC1),MC is min(C,MC1).

/* 18) short_path(X,Y,L) - короткий путь по кол-ву ребер (поиск вширь)
iii D - является ли L кратчайшим путем из X в Y
iio ND - короткие пути из X в Y
*/
short_path(X,Y,L):-in_while([[X]],Y,L).
in_while(Ls,Y,L):- % раскручиваем список маршрутов, пока не пришли
	\+ in_sp(Ls,Y,L),in_all_next_routes(Ls,Ln),in_while(Ln,Y,L)
	;in_sp(Ls,Y,L).
in_sp(Ls,Y,L):-member(L,Ls),member(Y,L). % пришли ли мы в цель
in_all_next_routes(L,Lr):-in_spread(L,[],Lr). % все следующие маршруты
% распространяемся по графу или идем по всем путям на 1 шаг
in_spread([],Lr,Lr).
in_spread([L1|LT],Lp,Lr):-in_go(L1,Ln),\+ member(Ln,Lp),
	in_spread([L1|LT],[Ln|Lp],Lr),!.
in_spread([_|LT],Lp,Lr):-in_spread(LT,Lp,Lr).
in_go(L,Lr):-in_next_vertex(L,Y),in_add_v(L,Y,Lr). % 1 шаг по пути
in_next_vertex(L,Y):-in_next_step(L,L,Y). % следующая вершина
in_next_step([X],Lp,Y):-!,medge(X,Y,_),\+ member(Y,Lp).
in_next_step([_|T],Lp,Y):-in_next_step(T,Lp,Y).
% добавить вершину в путь (в конец списка)
in_add_v([],Y,[Y]).
in_add_v([X|T],Y,[X|Tr]):-in_add_v(T,Y,Tr).

/* 19) cyclic - граф является циклическим
 D - цикличный или false
*/
cyclic:-medge(X,Y,_),findall(P,path(X,Y,P),L),length(L,N),N=\=1,N=\=0,!.

/* 20) is_connected - граф является связным
 D - связный или false
*/
is_connected:-medge(X,_,_),medge(Y,_,_),\+ path(X,Y,_),!,fail.
is_connected.



