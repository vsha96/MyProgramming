data Expr = Const Int           -- константа целого типа
          | Var String          -- имя переменной
          | Binary Op Expr Expr -- бинарная операция

data Op = Plus  -- сложение
        | Minus -- вычитание
        | Mul   -- умножение
        | Div   -- целочисленное деление

type Env = [(String, Int)]

-- data Either a b = Left a | Right b

data Error = ZERO_DIV | VAR_UNDEF String deriving Show

evalExpr :: Env -> Expr -> Either [Error] Int
evalExpr _ (Const c) = Right c
evalExpr env (Var x) 
  = case lookup x env of
    Nothing -> Left [VAR_UNDEF x]
    Just x  -> Right x
evalExpr env (Binary op exp1 exp2)
  = process op (evalExpr env exp1) (evalExpr env exp2)
    where
      process f op1 op2 = case (f , (op1 , op2)) of
        (Div , (Right a , Right 0)) -> Left [ZERO_DIV]
        (Div , (Left a , Right 0))  -> Left (a ++ [ZERO_DIV])
        (_ , (Left a , Left b))     -> Left (a ++ b)
        (_ , (Left a , _))          -> Left a
        (_ , (_ , Left b))          -> Left b
        (Plus , (Right a, Right b)) -> Right (a+b)
        (Minus , (Right a, Right b))-> Right (a-b)
        (Mul , (Right a, Right b))  -> Right (a*b)
        (Div , (Right a, Right b))  -> Right (div a b)
                        



main = do
    print $ evalExpr [("x", 1)] (Const 5)
    print $ evalExpr [("x", 1), ("y", 2)] (Binary Div (Var "x") (Const (0)))
    print $ evalExpr [("x", 1), ("y", 2)] (Binary Div (Var "t") (Binary Div (Var "f") (Const (0))))
