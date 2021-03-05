--ghc 8.0.2

data BiTree a = Leaf a | BiTree a (BiTree a) (BiTree a)

sumValue:: (Num a) => BiTree a -> a
sumValue (Leaf a) = a
sumValue (BiTree a left right) = a + sumValue left + sumValue right

main = do

print $ sumValue (BiTree 1 (Leaf 0) (BiTree 4 (Leaf 7)(Leaf 3)))