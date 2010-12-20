module Lambda (Lambda(Var, App, Lam), free, substitute, bethaRed) where

    import List
    import Maybe

    data Lambda = Var String  	-- Variable
            | App Lambda Lambda -- Application
            | Lam String Lambda -- Abstraction

    
    {-- implement instance Show. --}
    instance Show Lambda where
        show (Var name) = name
        show (Lam x m) = "\\" ++ x ++ " . " ++ show m
        show (App left right) = bracesIf isAbstraction left ++ " " ++ bracesIf (not . isVariable) right where
            isAbstraction (Lam _ _) = True
            isAbstraction _ = False
            isVariable (Var _) = True
            isVariable _ = False
            bracesIf criteria term = if needBraces then "(" ++ representation ++ ")" else representation where
                 needBraces = criteria term
                 representation = show term


    {-- Имеет ли переменная по меньшей мере одно свободное вхождение в \-выражение? --}
    {-- x <- FV(m) ? --}
    free :: String -> Lambda -> Bool

    free x (Var y) = x == y

    free x (Lam y n) | x == y = False
                     | otherwise = free x n

    free x (App m n) = free x m || free x n
    
    
    {-- substitute t x r -- подстановка r в t вместо формального параметра x --}
    substitute :: Lambda -> String -> Lambda -> Lambda

    substitute var@(Var y) x r | y == x = r
                           | otherwise = var
    
    substitute term@(Lam y n) x m | y == x = term
                                  | not (free y m) = Lam y $ substitute n x m
                                  | otherwise = substitute (Lam z $ substitute n y $ Var z) x m
                                    where
                                        z = fromJust $ find (not . (`free` m)) variableNames
                                        -- бесконечный список имён переменных
                                        variableNames = map (:[]) alphabet ++ (concat $ map (\i -> map (:show i) alphabet) [1..])
                                        alphabet = ['a'..'z']
    
    substitute (App left right) x m = App (substitute left x m) $ substitute right x m


    {-- Бета-редукция ( подстановка в абстракцию ) --}
    bethaRed :: Lambda -> Lambda -> Lambda
    
    -- Бета-конверсия
    bethaRed (Lam x n) = substitute n x
    

