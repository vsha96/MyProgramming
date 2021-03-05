--ghc 8.0.2

myreverse:: [a]->[a]
myreverse = foldl (\acc x -> x:acc) []

main = print (myreverse [1,2,3,4,6])