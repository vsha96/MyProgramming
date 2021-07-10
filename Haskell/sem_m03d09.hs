-- ТИПЫ

--data List a
--  = Nil
--  | Cons a (List a)

--[([a], b)]

-- функция для создания списков
--(:) :: a -> [a] -> [a]

--length :: [a] -> Int
--length [] = 0
--length Cons a l = 1 + (length l)

-- списки с прогрессией
{-
[11, 9..0]
[1..10]
take 10 [1..]
-}


-- делаем свой бесконечный тип (!непустой)
data Stream a = StreamC a (Stream a)
    deriving Show

ones :: (Fractional a) => Stream a
ones = StreamC 1 ones


takeStream :: Int -> Stream a -> [a]
takeStream n (StreamC a (s)) | n <= 0    = []
                             | otherwise = a : takeStream (n-1) s

streamFrom :: (Fractional a) => a -> Stream a
streamFrom n = StreamC n $ streamFrom (n + 1)

{-
showStream :: Stream a -> String
showStream a = "{" ++  ++ "}"
-}

mapStream :: (a -> b) -> Stream a -> Stream b
mapStream f (StreamC a s) = StreamC (f a) (mapStream f s)

meanStream :: (Fractional a) => Stream a -> Stream a
meanStream (StreamC a s) = func a 1 s
    where
        func x n (StreamC x_new st) = StreamC (x / n) (func (x+x_new) (n+1) st)

-- LIST COMPREHENSION

l1 :: [Int]
l1 = [x^2 | x <- [1..4]]

squares :: [Int] -> [Int]
squares l = [x^2 | x <- l]

guard2 :: [Int] -> [Int] -> [Int]
guard2 l1 l2 = [x*y | x <- l1, y <- l2, x < y]

-- таким образом переписываются стандартные функции
-- map f l  = [f x | x <- l]
-- filter f l = [x | x <- l, f x]

zip1 :: [Int] -> [Int] -> [(Int, Int)]
zip1 a b = [(x, y) | x <- a, y <- b]

-- constant
someList :: [String]
someList = ["hello", "world"]


