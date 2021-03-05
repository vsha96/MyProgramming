--ghc 8.0.2

data Tree = Empty | Node Int Tree Tree deriving Show

mulTrees:: Tree->Tree->Tree
mulTrees Empty _ = Empty
mulTrees _ Empty = Empty
mulTrees (Node x l1 r1) (Node y l2 r2) = (Node (x*y)  (mulTrees l1 l2) (mulTrees r1 r2))

main = do 
print $ mulTrees (Node 2 Empty (Node 3 Empty Empty)) (Node 6 (Node 3 Empty Empty) (Node 5 Empty Empty))