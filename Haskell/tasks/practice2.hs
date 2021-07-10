--ghc 8.0.2

fsym:: Char->[String]->String
fsym c [] = ""
fsym c (s:os) = if (c == head s) then s else fsym c os

fsym2:: Char->[String]->String
fsym2 c = head . filter (\s -> c == head s)

maxDist:: (Floating a, Ord a)=>(a,a)->[(a,a)]->a
maxDist p = maximum . map (dist p) 
    where dist (x1,y1) (x2,y2) = sqrt((y2-y1)^2+(x2-x1)^2)

gen:: [(Int,Char)]->String
gen = foldr (++) "" . map (\(size, c) -> replicate size c)

--concatMap (\(n, x) -> replicate n x) [(2, 'a'),(3, 'b'), (1, 'c')] == "aabbbc"
myConcatMap:: (a->[b])->[a]->[b]
myConcatMap f = foldr (++) [] . map f


type Point = (Float, Float)

rectangular:: Point->Point->Point->Bool
rectangular p1 p2 p3 = (a^2+b^2==c^2)||(a^2+c^2==b^2)||(b^2+c^2==a)
    where a = dist p1 p2
          b = dist p1 p3
          c = dist p2 p3
          dist (x1,y1) (x2,y2) = sqrt((y2-y1)^2+(x2-x1)^2) 

main = do
--print $ fsym 'd' ["cat","dog","pig","duck"]
--print $ fsym2 'd' ["cat","dog","pig","duck"]
--print $ maxDist (0,0) [(1,1),(-1,-2),(5,5)]
--print $ gen [(2, 'a'),(3, 'b'), (1, 'c')]
--print $ gen []
--print $ concatMap (\(n, x) -> replicate n x) [(2, 'a'),(3, 'b'), (1, 'c')] 
print $ rectangular (0,0) (0,3) (4,0)