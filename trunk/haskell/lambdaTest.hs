import Lambda

-- вспомогательные переменные, чтоб не писать везде Var "smth"
f = Var "f"
x = Var "x"
g = Var "g"
z = Var "z"

-- Y-комбинатор
y = Lam "f" $ App q q
    where
        q = Lam "x" $ App f $ App x x

checkShow description x = putStrLn $ description ++ ": " ++ show x ++ "\n"

checkFree variable term = putStrLn $ variable ++ " is free variable of `" ++ show term ++ "` ? " ++ show (free variable term) ++ "\n"

checkSubstitution original variable substitution =
    putStrLn $ "substituted " ++ variable ++ " in `" ++ show original ++ "` to `" ++ show substitution ++ "` and got `" ++ show result ++ "`\n"
    where
        result = substitute original variable substitution

checkBetha a v =
    putStrLn $ "beta( `" ++ show a ++ "` , `" ++ show v ++ "` ) = `" ++ show (bethaRed a v) ++ "`\n"



main = do
    let bigApplication = foldl1 App $ map (Var . (:[])) ['a'..'z']
    let bigAbstraction = foldr Lam z $ map (:[]) ['a'..'y']
    
    checkShow "id" $ Lam "x" x
    checkShow "Y" y
    checkShow "bigApplication" bigApplication
    checkShow "bigAbstraction" bigAbstraction
    
    putStrLn ""
    
    checkFree "f" y
    checkFree "f" $ f
    checkFree "x" $ Lam "x" g
    checkFree "g" $ Lam "x" g
    checkFree "x" $ App (Lam "x" g) x
    checkFree "x" $ App (Lam "g" $ App g x) f
    checkFree "g" $ App (Lam "g" $ App g x) f
    checkFree "f" $ App (Lam "g" $ App g x) f
    
    putStrLn ""

    checkSubstitution y "f" g
    checkSubstitution (App (Lam "g" $ App g x) f) "x" $ Lam "f" $ App f g
    checkSubstitution (Lam "x" (App f x)) "f" bigApplication
    checkSubstitution (Lam "x" (App f x)) "f" bigAbstraction
    
    putStrLn ""
    
    checkBetha y g
    checkBetha y y
    checkBetha (Lam "x" x) f
    checkBetha (Lam "x" $ Lam "f" $ App f x) f
