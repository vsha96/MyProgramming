--ghc 8.0.2

data BiTree a = Leaf a | BiTree a (BiTree a) (BiTree a) deriving Show

foldtree:: (a->a->a->a) -> BiTree a -> a
foldtree f (Leaf y) = y
foldtree f (BiTree y left right) = f y (foldtree f left) (foldtree f right)

mapTree :: (a -> b) -> BiTree a -> BiTree b
mapTree f (Leaf v) = Leaf (f v)
mapTree f (BiTree v l r) = BiTree (f v) (mapTree f l) (mapTree f r)

hasvalue:: (Eq a) => a -> BiTree a -> Bool
hasvalue v = foldtree (\x y z -> x || y || z) . mapTree (\x -> x == v) 

main = do
print $ foldtree (\x y z -> min x (min y z)) (BiTree 1 (Leaf 5) (BiTree (-4) (Leaf 7)(Leaf 3)))
print $ foldtree (\x y z -> x+y+z) (BiTree 1 (Leaf 5) (BiTree (-4) (Leaf 7)(Leaf 3)))
print $ foldtree (\x y z -> x || y || z) (mapTree (\x -> x==5) (BiTree 1 (Leaf 5) (BiTree (-4) (Leaf 7)(Leaf 3))))
print $ hasvalue 5 (BiTree 1 (Leaf 5) (BiTree (-4) (Leaf 7)(Leaf 3)))
print $ hasvalue 2 (BiTree 1 (Leaf 5) (BiTree (-4) (Leaf 7)(Leaf 3)))