--ghc 8.0.2

listp:: (Num a, Ord a) => [a]->Bool
listp [x] = x > 0
listp (x:xs) | x > 0 = listp xs
            | otherwise = False

listp2:: (Num a, Ord a) => [a] -> Bool
listp2 = foldr (\x acc -> acc && (x > 0)) True

main = do
print (listp [1,2,3,4,5,6])
print (listp [1,2,3,-4,5,6])