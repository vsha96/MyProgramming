--ghc 8.0.2

data Tree a = Empty | Node a (Tree a) (Tree a) deriving Show

-- Дано дерево поиска
-- Описать на Хаскеле тип дерева и составить функции для:

-- a) вычисления минимального значения узла в дереве
minSTree:: Tree a -> a
minSTree (Node a Empty _) = a
minSTree (Node _ l _) = minSTree l

-- b) вставки в дерево заданного значения x
insertSTree:: (Ord a, Eq a) => a -> Tree a -> Tree a
insertSTree x Empty = Node x Empty Empty
insertSTree x (Node y l r) | x < y = Node y (insertSTree x l) r
                           | x == y = Node y l r
                           | otherwise = Node y l (insertSTree x r)

-- c) вычисления пути к заданному значению x
calcPath:: (Ord a) => a -> Tree a -> [a]
calcPath x Empty = []
calcPath x (Node y l r) | x == y = [y]
                        | x > y = y : (calcPath x r)
                        | x < y = y : (calcPath x l)

main = do
--print $ minSTree (Node 5 (Node 2 (Node 1 Empty Empty) Empty) (Node 7 Empty Empty))
--print $ insertSTree 6 (Node 5 (Node 2 (Node 1 Empty Empty) Empty) (Node 7 Empty Empty))
--print $ insertSTree 4 (Node 5 (Node 2 (Node 1 Empty Empty) Empty) (Node 7 Empty Empty))
print $ calcPath 3 (Node 5 (Node 2 (Node 1 Empty Empty) Empty) (Node 7 Empty Empty))