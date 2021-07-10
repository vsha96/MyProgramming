--ghc 8.0.2

data BiTree a = Leaf a | BiTree a (BiTree a) (BiTree a)

hasvalue :: (Ord a) => a -> BiTree a -> Bool
hasvalue x (Leaf y) = (x==y)
hasvalue x (BiTree y left right) = (x == y) || (hasvalue x left) || (hasvalue x right)

main = do
print $ hasvalue 1 (BiTree 1 (Leaf 0) (BiTree (-4) (Leaf 7)(Leaf 3)))