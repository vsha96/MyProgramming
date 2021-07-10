-- ДЗ8:

data Tree a = Empty | Node a (Tree a) (Tree a) deriving (Show)

instance Foldable Tree where
  foldMap f Empty = mempty
  foldMap f (Node x l r) = f x <> foldMap f l <> foldMap f r



-- ***************************************************
-- 1. Реализовать instance Monoid для следующих типов:
-- ***************************************************

newtype Max a = Max { getMax :: a } deriving Show
newtype Min a = Min { getMin :: a } deriving Show

{-
>>> testTree2 = Node 1 (Node 2 Empty Empty ) (Node 4 Empty Empty)
-}

instance (Ord a, Bounded a) => Monoid (Max a) where
  mempty = Max minBound
instance (Ord a) => Semigroup (Max a) where
    (<>) (Max a) (Max b) | a < b = (Max b)
                         | otherwise = (Max a)

{-
>>> foldMap Min testTree2 :: Min Int
Min {getMin = 1}
-}

instance (Ord a, Bounded a) => Monoid (Min a) where
  mempty = Min maxBound
instance (Ord a) => Semigroup (Min a) where
    (<>) (Min a) (Min b) | a < b = (Min a)
                         | otherwise = (Min b)

{-
>>> foldMap Max testTree2 :: Max Int
Max {getMax = 4}
-}



-- ***************************************************
-- 2. Реализовать instance Monoid для следующих типов:
-- ***************************************************

newtype First a = First { getFirst :: Maybe a } deriving Show
newtype Last a = Last { getLast :: Maybe a } deriving Show

instance Monoid (First a) where
  mempty = First Nothing
instance Semigroup (First a) where
  (<>) (First Nothing) (First b) = First b
  (<>) (First (Just a)) _ = First (Just a)

{-
>>> foldMap First [Nothing, Just 42, Nothing, Just 10]
First {getFirst = Just 42}
-}

instance Monoid (Last a) where
  mempty = Last Nothing
instance Semigroup (Last a) where
  (<>) (Last a) (Last Nothing) = Last a
  (<>) _ (Last (Just b)) = Last (Just b)

{-
>>> foldMap Last [Nothing, Just 42, Nothing, Just 10]
Last {getLast = Just 10}
-}



-- ***********************************************
-- 3. Тип Mean a хранит кол-во значений и среднее, 
--   из которых это среднее получено. 
--   Реализовать для него instance Monoid:
-- ***********************************************

data Mean a = Mean Int a deriving Show

instance (Num a, Fractional a) => Monoid (Mean a) where
    mempty = Mean 0 z
      where
        z = fromIntegral 0
instance (Num a, Fractional a) => Semigroup (Mean a) where
  (<>) (Mean c1 s1) (Mean c2 s2) = 
    if (c1+c2)/=0 then
      Mean (c1+c2) ((s1*cc1+s2*cc2)/(cc1+cc2))
    else
      mempty
    where
      cc1 = fromIntegral c1
      cc2 = fromIntegral c2

{-
>>> Mean 2 3 <> Mean 1 0
Mean 3 2.0
>>> Mean 0 0 <> mempty
Mean 0 NaN
-}