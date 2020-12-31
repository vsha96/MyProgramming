--ghc 8.0.2

data Tree a = Leaf a | Tree (Tree a) (Tree a) deriving Show

sumLeafs:: (Num a) => Tree a -> a
sumLeafs (Leaf a) = a
sumLeafs (Tree l r) = (sumLeafs l) + (sumLeafs r)

main = do
print $ sumLeafs (Tree (Tree (Leaf 5) (Leaf 1)) (Tree (Tree (Leaf 2)  (Leaf 4)) (Leaf 9)))