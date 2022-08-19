mymember(E, [E|_]).
mymember(E, [_|T]):-mymember(E,T).
