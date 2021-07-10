--ghc 8.0.2

-- is it arithmetic sequence?
-- isArithm [2, 7, 12, 17] == True

isArithm::[Int]->Bool
isArithm l = foldl (&&) True (zipWith (==) (delta l) (tail (delta l)))
        where delta l = (zipWith (-) l (tail l))

main = do
print $ isArithm [2, 7, 12, 17] -- True
print $ isArithm [2, 8, 12, 17] -- False