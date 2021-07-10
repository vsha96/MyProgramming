newtype OrderedList a = OrderedList [a] deriving (Show)

instance Ord a => Semigroup (OrderedList a) where
  (<>) (OrderedList l1) (OrderedList l2) = OrderedList $ mergeList l1 l2
    where
      mergeList l1 [] = l1
      mergeList [] l2 = l2
      mergeList (x:xs) (y:ys) =
        if x < y then
          x : (mergeList xs (y:ys))
        else
          y : (mergeList (x:xs) ys)

instance Ord a => Monoid (OrderedList a) where
  mempty = OrderedList []

-- test:
--    (OrderedList [1, 3, 4, 6, 7]) <> (OrderedList [-1, 3, 5, 8])

