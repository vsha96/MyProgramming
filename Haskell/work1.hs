--ghc 8.0.2

unzip_ :: [(a,b)] -> ([a], [b])
unzip_ [] = ([], [])
unzip_ (x:xs) = ( [(fst x)] ++ (fst(unzip_ xs)) , [(snd x)] ++ (snd(unzip_ xs)) )

mergeLists :: [a] -> [a] -> [a]
mergeLists [] a = a
mergeLists a [] = a
mergeLists (a:xa) (b:xb) = [a, b] ++ mergeLists xa xb

iterate_ :: Int -> (a -> a) -> a -> a
iterate_ n f a | n <= 0 = a
               | otherwise = iterate_ (n-1) f (f a)


qsort :: [Int] -> [Int]
qsort [] = []
qsort (c:a) = qsort b ++ [c] ++ qsort d
    where  b = filter (< c) a
           d = filter (>= c) a