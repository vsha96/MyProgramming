--ghc 8.0.2

data BiTree a = Leaf a | BiTree a (BiTree a) (BiTree a)

minvalue :: (Ord a) => BiTree a -> a
minvalue (Leaf a) = a
minvalue (BiTree a left right) = min (min (minvalue left) (minvalue right)) a

main = do
print $ minvalue (BiTree 1 (Leaf 0) (BiTree (-4) (Leaf 7)(Leaf 3)))