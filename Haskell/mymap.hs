--ghc 8.0.2

mymap:: (a->b)->[a]->[b]
mymap f = foldr (\x acc -> (f x):acc) []

main = do
print (mymap (\ x -> x + 1) [1,2,3,4,6])