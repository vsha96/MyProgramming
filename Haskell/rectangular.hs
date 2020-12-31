--ghc 8.0.2

type Point = (Float, Float)

rectangular:: Point->Point->Point->Bool
rectangular p1 p2 p3 = a==b && b==c
    where a = dist p1 p2
          b = dist p1 p3
          c = dist p2 p3
          dist (x1,y1) (x2,y2) = sqrt((y2-y1)^2+(x2-x1)^2) 

main = do
print $ rectangular (-2,0) (2,0) (0,sqrt(12))
print $ rectangular (-2,0) (2,0) (0,5)