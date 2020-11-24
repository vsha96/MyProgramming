--ghc 8.0.2

myelem2:: (Eq a) => a->[a]->Bool
myelem2 a = foldl (\acc x -> acc || (a == x)) False

main = do
print (myelem2 4 [1,2,3,4,6])
print (myelem2 5 [1,2,3,4,6])