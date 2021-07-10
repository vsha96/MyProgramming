-ghc 8.0.2

myfind::  Int -> [(String, Int)] -> [String]
myfind x = map fst . filter (\(name, age) -> (age == x))

main = do
print ( myfind 20 [("Ivan",20), ("Serg",19), ("Den",21), ("Ramos",20), ("Ella",20)] )