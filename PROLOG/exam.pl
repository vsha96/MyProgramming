g(L1,L2,X) :- gg(L1,L2,X,[]).
gg(_, [], Acc, Acc).
gg(L1,[Y|L2],X,Acc):-
    member(E1,L1),
    member(E2,L1),
    E1 =\= E2,
    N is E1+E2,
    member(N,[Y|L2]),!,
    add_member(E1, Acc, NewAcc),
    add_member(E2, NewAcc, NewAcc1),
    gg(L1, L2, X, NewAcc1).

add_member(E, Acc, NewAcc) :-
    member(E, Acc), !, NewAcc = Acc.
add_member(E, Acc, [E | Acc]).


/**
g(L1,L2,X) :- gg(L1,L2,X,[]).

gg(_, [], Acc, Acc).
gg(L1, [Y|Ys], Lr, Acc) :-
    %write('!!! Ys = '),print(Ys),writeln(''),
    find_member(L1, L1, Y, Lr1, []),
    append(Lr1, Acc, NewAcc),
    print(NewAcc),
    gg(L1, Ys, Lr, NewAcc).

find_member(_, [], _, Lr, Lr).

find_member(L1, [X|Xs], Y, Lr, Acc) :-
    %write('find_member: X = '),print(X),writeln(''),
    %write('find_member: Xs = '),print(Xs),writeln(''),
    N is (Y - X),
    %write('find_member: '),print(Y-X=N),writeln(''),
    member(N, L1),!,
    \+ member(N, Acc),
    NewAcc = [N | Acc],
    find_member(L1, Xs, Y, Lr, NewAcc).
find_member(L1, [_|Xs], Y, Lr, Acc) :-
    find_member(L1, Xs, Y, Lr, Acc).
**/



/**
gg([X|Xs], [Y|Ys], Lr, Acc) :-
    N is (Y-X),
    member(N, [X|Xs]),!,
    append([N], Acc, NewAcc),
    gg([X|Xs], Ys, Lr, NewAcc).


gg([X|Xs], [Y|Ys], Lr, Acc) :-
**/

