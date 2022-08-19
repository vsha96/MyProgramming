myreverse([], []).
myreverse([X | T], L):-myreverse(T,T1), append(T1, [X], L).

