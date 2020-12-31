--ghc 8.0.2

data BiTree a = Leaf a | BiTree a (BiTree a) (BiTree a)

depth:: (Num a) => BiTree a -> Int
depth (Leaf a) = 1
depth (BiTree a left right) = max (depth left) (depth right) + 1

main = do
print $ depth (BiTree 1 (Leaf 0) (BiTree 4 (Leaf 7)(Leaf 3)))