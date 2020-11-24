--ghc 8.0.2

myflatten:: [[a]]->[a]
myflatten [] = []
myflatten ([]:xs) = myflatten xs
myflatten ((x1 : x2) : xs) = x1 : myflatten (x2 : xs)

main = do
print (myflatten [[1,2], [3,4], [5,8,9]])