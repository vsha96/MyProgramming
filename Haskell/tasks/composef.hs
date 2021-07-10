--ghc 8.0.2

composef1:: [(a->a)]->a->a
composef1 [fn] x = fn x
composef1 (f:fn) x = (f (composef1 fn x))

composef2:: [(a->a)]->a->[a]
composef2 [fn] x = [fn x]
composef2 (f:fn) x = (f x) : (composef2 fn x)

composef3:: [(a->a)]->a->[a]
composef3 l x = map (\f -> f x) l

main = do
print (composef1 [(*2),(+1)] 2)
print (composef2 [(*2),(+1)] 2)
print (composef3 [(*5),(+2),(\ x -> x - 5)] 2)