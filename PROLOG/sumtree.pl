sumTree(0, nil).
sumTree(Sum, tree(N,L,R)):-sumTree(NL, L),sumTree(NR, R),Sum is NL+NR+N.
%sumTree(Sum, tree(N,L,R)):-sumTree(NL, L),sumTree(NR, R),Sum = NL+NR+N.
% TEST
% sumTree(X,tree(1,tree(2,nil,nil), tree(3,nil,nil))).
vertical(segm(point(X,Y1),point(X,Y2))).
