-- ПОЛИМОРФИЗМ
class Name a where
	func1 :: a -> String
	func2 :: Int -> Int -> a

instance Name Type where
	func = ...

showMin :: (Show a, Ord a) => a -> a -> String
showMin x y = show (min x y)

f3 :: (Bool -> a) -> a
f3 f = f True
f3 f = f False

f4 :: (a -> Bool) ->
f4 _ = True
f4 _ = False

f5 :: (a -> Bool) -> [a] -> Bool
-- здесь всего 2 осмысленные функции могут быть

data PairType a b = Pair a b
-- тут разные пространства имен на разных уровнях
-- так что лучше называй их по-разному, чтобы осмыслить

type IntStr = PairType Int String
type CharBool = PairType Char Bool

-- как мы объявляем константы
pi :: Float
pi = 3.14159

-- вот также теперь, только со своим типом
intStr :: IntStr
intStr = Pair 1 "one"

chBool :: CharBool
chBool = Pair 'a' True

-- посмотрим на опциональный тип
data Maybe a = Nothing | Just a

f1 :: Maybe a -> Bool
f1 Nothing = True
f1 _ = False
-- вообще такая функция есть, это isNothing
-- также есть isJust

f2 :: a -> Maybe a -> a
fromMaybe x Nothing = x
fromMaybe _ (Just x) = x

f3 :: [a] -> Maybe a
listToMaybe [] = Nothing
listToMaybe (x:xs) = Just x

-- пример
$ cmd --verbose --opt1 val
["--verbose", "--opt1", "val"]

data Args = Args
	{ isVerbose :: Bool
 ...
	}
	-- нужно обработать список аргументов
	-- и заполнить args

-- дальше идем
f4 :: b -> (a -> b) -> Maybe a -> b
maybe x _ Nothing = x
maybe x f (Just v) = f v --нужно (just v) для pattern matching

type Cell = Maybe Int

-- есть тип для обработки ошибок (его так используют часто)
data Either a b = Left a | Right b

f1 :: a -> Either a b -> a
fromLeft _ (Left x) = x
fromLeft x _ = x

fromRight :: b -> Either a b -> b

either :: (a -> c) -> (b -> c) -> Either a b -> c

-- пример
data GameConfig = ...
data FileError
	= FileNotFound
	| PermissionDenied
	| Wrong

-- не забудь IO, так как с реальным миром взаимодействуем
readConfig :: FilePath -> IO (Either FileError GameConfig)

data Expr
	= Const Int
	| Var String
	| Plus Expr Expr

-- переменная типа
type Env = [(String, Int)]

lookup :: (Eq a) => a -> [(a, b)] -> Maybe b
lookup :: String -> [(String, Int)] -> Maybe Int

evalExpr :: Env -> Expr -> Either String Int

-- ЗАДАЧА
--ghc 8.0.2
data Expr
  = Const Int
  | Var String
  | Plus Expr Expr

type Env = [(String, Int)]

evalExpr :: Env -> Expr -> Either String Int
evalExpr env (Const x) = Right x
evalExpr env (Var x) = case lookup x env of
                            Nothing -> Left ("var is undefined: " ++ x)
                            Just x  -> Right x
evalExpr env (Plus (exp1) (exp2)) = case (evalExpr env exp1, evalExpr env exp2) of
                            (Right x, Right y) -> Right (x + y)
                            (Left x, _) -> Left x
                            (_, Left y) -> Left y

main = do
print $ evalExpr [("x", 5), ("y", 10)] (Plus (Var "t") (Var "y"))
print $ evalExpr [("x", 5), ("y", 10)] (Plus (Const (-9)) (Var "y"))







