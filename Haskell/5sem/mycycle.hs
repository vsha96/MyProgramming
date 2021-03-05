--ghc 8.0.2

mycycle:: [a]->[a]
mycycle l = l ++ (mycycle l)

main = do
print (take 9 (mycycle [1,2,3,4]))