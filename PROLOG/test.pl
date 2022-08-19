parent(mary, david).
parent(mary, erich).
parent(mary, anton).
parent(david, bob).
woman(mary).
man(david).
man(anton).
man(erich).
man(bob).
brother(X,Y):-parent(Z,Y),parent(Z,X),man(X),dif(X,Y).
uncle(X,Y):-parent(Z,Y),brother(X,Z).
ancestor(X,Y):-parent(X,Y).
ancestor(X,Y):-parent(Z,Y),ancestor(X,Z).


