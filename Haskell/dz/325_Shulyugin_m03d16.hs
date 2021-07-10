data Stream a = StreamC a (Stream a)
    deriving Show

takeStream :: Int -> Stream a -> [a]
takeStream n (StreamC a (s)) | n <= 0    = []
                             | otherwise = a : takeStream (n-1) s

-- **************************************
-- **********ДОМАШНЕЕ_ЗАДАНИЕ_4**********
-- **************************************

-- 1. Реализовать следующие функции для работы с бесконечными потоками:

-- Аналоги zip и zipWith

zipStream :: Stream a -> Stream b -> Stream (a, b)
zipStream (StreamC a as) (StreamC b bs) = StreamC (a, b) $ zipStream as bs
-- test: 
--      takeStream 5 $ zipStream ones (streamFrom 2)

zipStreamWith :: (a -> b -> c) -> Stream a -> Stream b -> Stream c
zipStreamWith f (StreamC a as) (StreamC b bs) = StreamC (f a b) (zipStreamWith f as bs)
-- test:
--      takeStream 5 $ zipStreamWith (+) ones ones


-- Бесконечный поток чисел Фибоначчи.

fibStream :: Stream Int
fibStream = (StreamC 1 (StreamC 1 (fib fibStream)))
  where
    fib (StreamC x1 (StreamC x2 xs)) = (StreamC (x1+x2) (fib (StreamC x2 xs)))
-- 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 ...
-- test:
--      takeStream 10 $ fibStream 



-- 2. Реализовать следующие функции, используя абстракцию списков:

-- Пифагоровы тройки:
pythTriples :: [(Int, Int, Int)]
pythTriples = [(x,y,z)
                | x<-[1,2..100]
                , y<-[1,2..100]
                , z<-[1,2..200]
                , x<y, y<z, z^2==x^2+y^2]
-- test:
--      take 10 $ pythTriples

-- Простые числа:
primes :: [Int]
primes = [x | x<-[2,3..], (checkPrime x)]
  where
    checkPrime y = null [z | z<-[2..y-1], (mod y z)==0]
-- test:
--      take 100 $ primes