:-dynamic fib_db/2.
fib(0,1):-!.
fib(1,1):-!.
fib(N,F):-fib_db(N,F),!.
fib(N,F):-
	N1 is N-1, fib(N1,F1),
	N2 is N-2, fib(N2,F2),
	F is F1+F2, asserta(fib_db(N,F)).
