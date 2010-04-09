type Name = String

data Term = Func Name [Term] | Var Name deriving (Eq)
-- отображение термов
instance Show Term where
	show (Func name args) = name ++ "(" ++ (show' args) ++ ")"
		where
			show' [arg] = show arg
			show' (arg:others) = (show arg) ++ ", " ++ (show' others)
	show (Var name) = name

-- «амена переменной на терм
data Replacement = Replacement Term Term deriving (Eq)
instance Show Replacement where
	show (Replacement v t) = (show t) ++ "/" ++ (show v)

-- унификатор - набор замен
type Unificator = [Replacement]

isVariable (Var _) = True
isVariable _ = False

apply :: Replacement -> Term -> Term
apply r (Func name args) = Func name (map (apply r) args)
apply (Replacement v t) x
	| x == v = t
	| otherwise = x

lcu :: [Term] -> Maybe Unificator
lcu w =
	if result == Nothing then Nothing
	else Just (reverse (unificator))
	where
		result = step1 w
		Just unificator = result
		step1 :: [Term] -> Maybe Unificator
		step1 w =
			step2 u sigma
			where
				u = w
				sigma = []
				
				step2 :: [Term] -> Unificator -> Maybe Unificator
				step2 u sigma =
					if disjunct u then Just sigma
					else step3 u sigma d
					where
						disjunct :: [Term] -> Bool
						disjunct (x:xs) = all (==x) xs
						Just d =
							mismatch u
							where
								mismatch :: [Term] -> Maybe [Term]
								mismatch terms =
									-- если термы не совпадают (по имени)
									if nameMismatch terms then
										Just terms
									else
										-- если совпадают то смотрим на списки аргументов
										-- но только если это функции
										if all isVariable terms then Nothing
										else mismatch' argumentsList
									where
										argumentsList = map getArguments terms
										getArguments (Func _ args) = args
										mismatch' :: [[Term]] -> Maybe [Term]
										mismatch' argumentsList | all (>0) (map length argumentsList) =
											if firstMismatch == Nothing then
												mismatch' nextArguments
											else
												firstMismatch
											where
												firstArguments = map head argumentsList
												nextArguments = map tail argumentsList
												firstMismatch = mismatch firstArguments
										mismatch' argumentsList | all (==0) (map length argumentsList) =
											Nothing
										nameMismatch :: [Term] -> Bool
										nameMismatch (first:others) =
											any (\x -> getName x /= etalon) others
											where
												etalon = getName first
												getName (Func name _) = name
												getName (Var name) = name
						step3 :: [Term] -> Unificator -> [Term] -> Maybe Unificator
						step3 u sigma d =
							step4 u sigma candidates
							where
								candidates =
									[Replacement v t | t <- d, v <- d, isVariable v, not(t `contains` v)]
									where
										contains :: Term -> Term -> Bool
										(Var t) `contains` v = (Var t) == v
										(Func _ args) `contains` v = any (\arg -> arg `contains` v) args
								step4 _ _ [] = Nothing
								step4 u sigma (repl:_) =
									step2 newU newSigma
									where
										newU = map (apply repl) u
										newSigma = repl : sigma

lcuDemo :: [Term] -> String
lcuDemo terms =
	"lcu: " ++ (show mu) ++ "; Result: " ++ show (result mu)
	where
		mu = lcu terms
		result Nothing = Nothing
		result (Just u) = Just (apply' u (head terms))
		apply' [] term = term
		apply' (repl:rs) term = apply' rs (apply repl term)
