{-# LANGUAGE InstanceSigs, ViewPatterns #-}
-- ДЗ7:
-- ***********************
-- 1. Определить вид типов
-- ***********************

data C a b = C a (C b a) | CN
-- C b a :: *
-- C a :: * -> *
-- a :: *
-- b :: *
-- C :: * -> * -> *

data E = E
-- E :: *

data F a b = F (a -> b)
-- a -> b :: *
-- a :: *
-- b :: *
-- F :: * -> * -> *

data G a b = G1 (a -> b) | G2 (b -> a)
-- G :: * -> * -> *

data H a b = H ((b -> a) -> a)
-- H :: * -> * -> *

data L f = L f (L f)
-- L :: * -> *

data N r f a = N ((a -> f r) -> f r)
-- f :: * -> *
-- N :: * -> (* -> *) -> * -> *



-- ***************************************************
-- 2. Определить instance Functor для следующих типов:
-- ***************************************************

data Stream a = Stream a (Stream a)

instance Functor Stream where
  fmap f (Stream x xs) = Stream (f x) (fmap f xs)

data Pair a b = Pair a b

instance Functor (Pair c) where
  fmap :: (a -> b) -> Pair c a -> Pair c b
  fmap f (Pair c a) = Pair c (f a)

data Arrow r a = Arrow (r -> a)

instance Functor (Arrow c) where
  fmap :: (a -> b) -> Arrow c a -> Arrow c b
  fmap f (Arrow c) = Arrow (f . c)


