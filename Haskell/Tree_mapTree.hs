--ghc 8.0.2

data Tree a = Node a | Tree a (Tree a) (Tree a) (Tree a) deriving Show

mapTree:: (a->b)->Tree a->Tree b
mapTree f (Node x) = Node (f x)
mapTree f (Tree x t1 t2 t3) = Tree (f x) (mapTree f t1) (mapTree f t2) (mapTree f t3)

main = do
print $ mapTree (\x -> x>0) (Tree 1 (Node 2) (Node 3) (Tree 6 (Node (-1)) (Node (-2)) (Node (-3))))
print $ mapTree (*2) (Tree 1 (Node 2) (Node 3) (Node (-3)))