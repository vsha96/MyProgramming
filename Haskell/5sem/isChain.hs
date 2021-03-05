--ghc 8.0.2

--isChain ["cat", "tree", "eat"] == True

isChain:: [String]->Bool
isChain l = foldl1 (&&) (zipWith (\x y -> last x == head y) l (tail l))

main = do
print $ isChain ["cat", "tree", "eat"]