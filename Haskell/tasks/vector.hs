--ghc 8.0.2

type Vector = [Float]
type Vec3 = (Float, Float, Float)

angle:: Vector-> Vector->Float
angle v1 v2 = (foldl1 (+) (zipWith (*) v1 v2))/modul(v1)/modul(v2)
    where modul [x1,x2,x3] = sqrt (x1^2+x2^2+x3^2) --тут ограничения на трехмерность

angle3:: Vec3->Vec3->Float
angle3 v1 v2 = (dot v1 v2) / (modul v1) / (modul v2)
    where dot (x1,x2,x3) (y1,y2,y3) = x1*y1+x2*y2+x3*y3
          modul (x1,x2,x3) = sqrt (x1^2+x2^2+x3^2)

main = do
print $ angle [1,1,1] [5,1,1] -- 0,77
print $ angle3 (1,1,1) (5,1,1)