edge(a,b,10).
edge(c,b,20).
edge(c,d,5).
edge(e,d,5).
edge(e,f,10).
edge(e,b,5).
edge(a,f,25).

/*
предикат для неориентированного графа
*/
medge(X,Y,Z):-edge(X,Y,Z);edge(Y,X,Z).

/*
путь из одной вершины в другую
(начало, конец, путь)
выводит все возможные пути
*/
path(Start,End,Route):-costpath(Start,End,Route,_).

/*
путь со стоимостью
(начало, конец, пусть, стоимость) 
выводит все пути со стоимостью
*/
costpath(S,E,Route,Cost):-
	ext_path(S,E,Route,[E],Cost).
ext_path(S,S,L,L,0):-!.
ext_path(S,E,L,Lp,Cost):-
	medge(E,T,Ct),\+ member(T,Lp),ext_path(S,T,L,[T|Lp],Ctn),
	Cost is Ct+Ctn.

/* 
путь с минимальной стоимостью
(начало, конец, стоимость*путь) 
выводит все пути с минимальной стоимостью
*/
min_costpath(S,E,Cost*Path):-
	findall(C*P,costpath(S,E,P,C),L),
	ext_mincost(L,Cost),
	member(Cost*Path,L).
ext_mincost([C*_],C):-!.
ext_mincost([C*_|T],MC):-ext_mincost(T,MC1),MC is min(C,MC1).

/*
короткий путь по кол-ву вершин
(начало, конец, путь)
*/
shortpath(S,E,L):-ext_sp(S,E,L,[]).
ext_sp(S,S,L,L):-!.
%ext_sp(S,E,L,Acc):-

%TODO что то нужно делать еще с накапл параметрмо
% добавлять туда вершины
next_step([Way|T],VisitedVL):-next_vertex(Way,VisitedVL).

next_vertex([V1], [T|VisitedVL]):-
	medge(V1,T,_),\+ member(T, VisitedVL).
next_vertex([_|T],VisitedVL):-
	next_vertex(T,VisitedVL).


%cycle

%connectivity



% TRASH_CODE
/* 
path(S,E,L):-ext_path(S,E,L,[E]).
%path(S,E,L):-ext_path(S,E,L,[S]).
ext_path(S,S,L,L):-!.
ext_path(S,E,L,Lp):-medge(E,T,_),\+ member(T,Lp),ext_path(S,T,L,[T|Lp]).
%ext_path(S,E,L,Lp):-medge(S,T,_),\+ member(T,Lp),ext_path(T,E,L,[T|Lp]).
*/

