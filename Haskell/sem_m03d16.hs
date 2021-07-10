-- Алгебраические типы данных

-- Тип-произведение
--      call произведением, т.к. кол-во значений возможных 
--      равно произведению кол-ва значений
{-
(a, b)
    и по сути то же самое
data Pair a b = PairCons a b
-}

-- Тип-сумма
--      call суммой, т.к. кол-во значений возможных 
--      равно сумме кол-ва значений
data Either a b = Left a | Right b
data Bool = True | False

--***********************************

data Sum a b = SumLeft a | SumRight b
data Prod a b = ProdC a b

prodToSum :: Prod a (Sum b c) -> Sum (Prod a b) (Prod a c)
prodToSum (ProdC a (SumLeft b)) = SumLeft (ProdC a b)
prodToSum (ProdC a (SumRight c)) = SumRight (ProdC a c)

sumToProd :: Sum (Prod a b) (Prod a c) -> Prod a (Sum b c)
sumToProd (SumLeft (ProdC a b)) = ProdC a (SumLeft b)
sumToProd (SumRight (ProdC a c)) = ProdC a (SumRight c)

--**************************
--*Опишем тележку покупателя
--**************************

-- module cart where
type Title = String

type RUB = Double

type SimpleCart = [(Title, RUB)]

total :: [(Title, RUB)] -> RUB

total1 :: SimpleCart -> RUB
total1 [] = 0
total1 ((_, cost) : items) = cost + total1 items

total2 :: SimpleCart -> RUB
total2 = sum . map snd

-- синонимы типов - это хорошо, но лучше свой тип данных
--      чтобы и операции возможные закрепить
-- поэтому можно use

newtype Amount = Amount Double

--!!! если use геттер, то там только ОДНО ПОЛЕ !!!







