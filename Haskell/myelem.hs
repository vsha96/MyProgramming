--ghc 8.0.2

myelem:: (Eq a) => a->[a]->Bool
myelem _ [] = False
myelem a (x:xs) | a == x = True
              | otherwise = myelem a xs

main = do
print (myelem 4 [1,2,3,4,6])
print (myelem 5 [1,2,3,4,6])