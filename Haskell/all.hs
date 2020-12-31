--ghc 8.0.2

--all (>0)[1,2,5,7,11]== True
--all (>0)[1,2,-5,7,11]== False

all1::(a->Bool)->[a]->Bool
all1 f [x] = f x
all1 f (x:xs) = (f x) && (all1 f xs)

all2::(a->Bool)->[a]->Bool
all2 f  = foldr1 (&&) . map f

main = do
print $ all1 (>0)[1,2,5,7,11]
print $ all1 (>0)[1,2,-5,7,11]
print $ all2 (>0)[1,2,5,7,11]
print $ all2 (>0)[1,2,5,7,-11]