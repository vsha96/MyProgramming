--ghc 8.0.2

-- getNames  'A' [('A', "Smith"),  ('J', "Brown"), ('A', "Taylor")] == ["A.Smith", "A.Taylor"]

getNames:: Char->[(Char,String)]->[String]
getNames c l = map (\(n,s)-> n : '.' : s) (filter (\(n,s) -> n == c) l)

main = do
print $ getNames 'A' [('A', "Smith"),  ('J', "Brown"), ('A', "Taylor")]