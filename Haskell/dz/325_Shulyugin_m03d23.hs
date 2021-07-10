-- ДЗ5:
-- ***************************
-- 1. Сколько значений у типа?
-- ***************************

data Shape
    = Circle Float
    | Rect Float Float

-- ОТВЕТ: inf + inf^2 ~ inf^2



-- ****************************************************
-- 2. Показать, что типы Maybe a и Sum One a изоморфны.
-- ****************************************************

-- data Maybe a = Nothing | Just a

data One = One deriving Show

data Sum a b = SumLeft a | SumRight b deriving Show

f1 :: Maybe a -> Sum One a
f1 Nothing = SumLeft One
f1 (Just a) = SumRight a

g1 :: Sum One a -> Maybe a
g1 (SumLeft One) = Nothing
g1 (SumRight a) = Just a



-- *****************************************************
-- 3. Показать, что a*1 = a, используя изоморфизм типов.
-- *****************************************************

data Prod a b = Prod a b deriving Show

-- if a*1 is acceptable, then a from Num

f2 :: (Prod a One) -> a
f2 (Prod a One) = a

g2 :: a -> (Prod a One)
g2 a = Prod a One



-- ***************************************************************************
-- 4. Вспомним, что тип Bool соответствует числу 2. Показать, что a + a = 2*a, 
--      используя изоморфизм соответствующих типов.
-- ***************************************************************************

-- data Bool = False | True

f3 :: (Sum a a) -> (Prod Bool a)
f3 (SumLeft a) = Prod False a
f3 (SumRight a) = Prod True a

g3 :: (Prod Bool a) -> (Sum a a)
g3 (Prod False a) = SumLeft a
g3 (Prod True a) = SumRight a



-- ***********************************************************************
-- 5. Исправить модель корзины в интернет-магазине: переписать все функции 
--      с новыми типами и добиться успешной компиляции.
-- ***********************************************************************

type Title = String

newtype Amount = Amount { unAmount :: Double } deriving Show

newtype RUB = RUB { unRUB :: Double } deriving Show

data CartElem = CartElem
  { cartAmount :: Amount
  , cartItemTitle :: Title
  , cartItemCost :: RUB
  }

-- TEST CART
testCart :: Cart
testCart = [(CartElem (Amount 0.5) "Item1" (RUB 1200))  -- cost  600
           ,(CartElem (Amount 1.2) "Item2" (RUB 1000))  -- cost 1200
           ,(CartElem (Amount 0.1) "Gold" (RUB 10000))] -- cost 1000


type Cart = [CartElem]

amountCost :: Amount -> RUB -> RUB
amountCost (Amount a) (RUB rub) = RUB (a*rub)

total4 :: Cart -> RUB
total4 = foldl f (RUB 0)
  where
    f :: RUB -> CartElem -> RUB
    f acc (CartElem amount _ cost) = RUB $ (unRUB acc) + (unRUB cost)*(unAmount amount)
--TEST :: 
-- total4 testCart 

total5 :: Cart -> Amount
total5 cart = Amount $ sum $ map (\(CartElem amount _ cost) -> unAmount amount) cart
--TEST :: 
-- total5 testCart 

