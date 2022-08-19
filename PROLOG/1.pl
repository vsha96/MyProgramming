% Шулюгин Иван 
% 425
% задача 0

% ?:- g(V, E, X)
%   X - клика
%   e.g.
%       вершины V = [1,2,3]
%       ребра   E = [[1,3], [2,3]...]
g(V,E,X) :- mset(V, X), klika(X,E), \+ less(V, E, X), !.

% граф является кликой
%   (т.е. нет таких вершин, которые были бы не соединены)
klika(X, E) :- \+ uncon_members(X, E).

% есть несоединенные вершины
uncon_members(X, E) :- member(X1,X), member(X2,X), X1 \= X2,
    \+ check_edge(E, [X1,X2]), !.

% есть ли такое ребро
check_edge(E, [X1, X2]) :- member([X1,X2], E),!.
check_edge(E, [X1, X2]) :- member([X2,X1], E),!.

% подмножество (берутся по порядку элементы)
mset([], []).
mset([X|XS], [X|L]) :- mset(XS, L).
mset([_|XS], L) :- mset(XS, L).

% длина списка
mlen([], 0).
mlen([_|XS], R) :- mlen(XS, TR), R is 1 + TR.

% список меньше по длине из возможных
less(V,E, X1) :- mset(V, X2), X1 \= X2,
    klika(X2,E), mlen(X1,N1), mlen(X2,N2), N1 < N2.



/**
g(L, X) :- my_set(L, X), check_divs(X), \+ less(X, L), !.


less(X1, L) :- my_set(L, X2), X1 \= X2, check_divs(X2),
    my_len(X1,N1), my_len(X2,N2), N1 < N2.

check_divs([]) :- !.
check_divs(X) :- member(Y1,X),member(Y2,X),Y1 =\= Y2,
    (is_div(Y1,Y2); is_div(Y2,Y1)),!, fail.
check_divs(_).

my_len([], 0).
my_len([_|XS], R) :- my_len(XS, TR), R is 1 + TR.

my_set([], []).
my_set([X|XS], [X|L]) :- my_set(XS, L).
my_set([_|XS], L) :- my_set(XS, L).


% Y is a divider of X
is_div(X, Y) :- M is mod(X, Y), M == 0.


* =======
* =======
* =======



g(L1,L2,X) :- mset(L1, X), check(X, L2), \+ greater(X, L1, L2),!.

mset([], []).
mset([X|XS], [X|L]) :- mset(XS, L).
mset([_|XS], L) :- mset(XS, L).

greater(X1, L, L2) :- mset(L, X2), X1 \= X2, check(X2, L2),
    mlen(X1,N1), mlen(X2,N2), N1 > N2.

mlen([], 0).
mlen([_|XS], R) :- mlen(XS, TR), R is 1 + TR.

 
check(_, []).
check(L1, [M | L2]) :- member(N1,L1), member(N2,L1), M =:= N1+N2,
    check(L1, L2).

**/
















