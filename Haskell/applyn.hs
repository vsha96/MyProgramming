--ghc 8.0.2

applyn:: (a->a) -> Int -> a -> a
applyn _ 0 a = a
applyn f n a = applyn f (n-1) (f a)

main = do
print (applyn (*2) 3 5)