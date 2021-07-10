--ghc 8.0.2

data BiTree t = Leaf t | BiTree t (BiTree t) (BiTree t) deriving Show 

--1
eqTrees:: (Eq a)=> BiTree a -> BiTree a -> Bool
eqTrees (Leaf a) (Leaf b) = a == b
eqTrees (BiTree x la ra) (BiTree y lb rb) =  (x == y) && (eqTrees la lb) && (eqTrees ra rb)
eqTrees _ _ = False

--N
pathLength::(Floating a)=>[(a,a)]->a
pathLength l = foldl (+) 0 (zipWith dist l (tail l))
    where dist (x1,y1) (x2,y2) = sqrt((x2-x1)^2+(y2-y1)^2)
    

main = do
--1
--print $ eqTrees (BiTree 1 (Leaf 0) (BiTree 4 (Leaf 7)(Leaf 3))) (BiTree 1 (Leaf 0) (BiTree 4 (Leaf 7)(Leaf 3)))
--print $ eqTrees (BiTree 1 (Leaf 0) (BiTree 4 (Leaf 7)(Leaf 3))) (BiTree 1 (Leaf 0) (BiTree 4 (Leaf 7)(Leaf 3)))

--N
--print $ pathLength [(1,1), (2,2), (3,4)]
--print $ pathLength [(1,1)]