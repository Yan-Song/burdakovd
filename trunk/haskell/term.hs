type Arity = Integer
data Term = Function Arity | Variable

termByName :: Char -> Maybe Term
-- f, g, h - функции арности 2
termByName 'f' = Just (Function 2)
termByName 'g' = Just (Function 2)
termByName 'h' = Just (Function 2)
-- p, q - функции арности 3
termByName 'p' = Just (Function 3)
termByName 'q' = Just (Function 3)
-- m - функция арности 1
termByName 'm' = Just (Function 1)
-- переменные
termByName 'x' = Just Variable
termByName 'y' = Just Variable
termByName 'z' = Just Variable
termByName 'u' = Just Variable
termByName 'v' = Just Variable
-- любой другой символ не является именем терма
termByName _ = Nothing

type Junk = String
-- Fail - строка не начинается с терма, Success - начинается, и после него идёт Junk
data ParseResult = Fail | Success Junk

parseTerm :: String -> ParseResult
parseTerm [] = Fail
parseTerm (first:chars) =
	parseTerm' term chars
	where
		term = termByName first
		
		parseTerm' :: (Maybe Term) -> String -> ParseResult
		
		-- Если строка начинается с имени переменной
		parseTerm' (Just Variable) chars = Success chars
		
		-- Если строка начинается с имени функции, то нужно считать
		-- открывающую скобку, аргументы и закрывающую скобку
		parseTerm' (Just (Function arity)) chars =
			(openBracket `before` (arguments arity) `before` closeBracket) chars
			where
				openBracket = parseChar '('
				closeBracket = parseChar ')'
				
				arguments :: Arity -> String -> ParseResult		
				-- ноль аргументов
				arguments 0 = Success
				-- один аргумент
				arguments 1 = argument
				-- более одного аргумента
				arguments arity =
					argument `before` comma `before` (arguments (arity - 1))
					where
						comma = parseChar ','
					
				-- аргумент это терм
				argument = parseTerm
				
				parseChar :: Char -> String -> ParseResult
				parseChar char =
					parse
					where
						parse (char:chars) = Success chars
						parse _ = Fail
						
				before :: (String -> ParseResult) -> (String -> ParseResult) -> (String -> ParseResult)
				f `before` g =
					g' . f
					where
						g' Fail = Fail
						g' (Success junk) = g junk
		
		-- если строка начинается с чего-то постороннего, то это не терм
		parseTerm' Nothing _ = Fail	

isTerm :: String -> Bool
isTerm s =
	isTerm' parsed
	where
		parsed = parseTerm s
		-- строка является термом если она состоит из терма за которым следует пустая строка
		isTerm' (Success "") = True
		isTerm' _ = False
