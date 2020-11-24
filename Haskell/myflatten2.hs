--ghc 8.0.2

myflatten2:: [[a]]->[a]
myflatten2 = foldr1 (\x acc -> x++acc)

main = do
print (myflatten2 [[1,2], [3,4], [5,8,9]])