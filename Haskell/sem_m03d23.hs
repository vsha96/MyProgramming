-- КЛАССЫ ТИПОВ

class PrettyPrint a where
  pprint :: a -> String

instance PrettyPrint a => PrettyPrint [a] where
    pprint [] = ""
    pprint (x:xs) = (pprint x) ++ "\n" ++ (pprint xs)

-- TEST
--  pprint ([1,2,3,4,5] :: [Int])
--  putStr $ pprint ([1,2,3,4,5] :: [Int])
instance PrettyPrint Int where
    pprint = show
