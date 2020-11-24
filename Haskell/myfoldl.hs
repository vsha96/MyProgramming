--ghc 8.0.2

myfoldl:: (a->b->a)->a->[b]->a
myfoldl f a [b] = f a b
myfoldl f a (x:xs) = myfoldl f (f a x) xs

main = print (myfoldl (\a b -> a + b) 10 [1,2,3,4,6])