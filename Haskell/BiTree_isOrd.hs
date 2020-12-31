--ghc 8.0.2

data BiTree a = Leaf a | BiTree a (BiTree a) (BiTree a) deriving Show

isOrd:: (Ord a) => [a] -> Bool
isOrd list = foldr1 (&&) (zipWith (>) list (tail list))

main = do
print $ isOrd [9,5,4,3,2,1]
print $ isOrd [9,5,4,6,2,1]