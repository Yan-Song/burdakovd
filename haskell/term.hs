type Arity = Integer
data Term = Function Arity | Variable

termByName :: Char -> Maybe Term
-- f, g, h - ������� ������� 2
termByName 'f' = Just (Function 2)
termByName 'g' = Just (Function 2)
termByName 'h' = Just (Function 2)
-- p, q - ������� ������� 3
termByName 'p' = Just (Function 3)
termByName 'q' = Just (Function 3)
-- m - ������� ������� 1
termByName 'm' = Just (Function 1)
-- ����������
termByName 'x' = Just Variable
termByName 'y' = Just Variable
termByName 'z' = Just Variable
termByName 'u' = Just Variable
termByName 'v' = Just Variable
-- ����� ������ ������ �� �������� ������ �����
termByName _ = Nothing

type Junk = String
-- Fail - ������ �� ���������� � �����, Success - ����������, � ����� ���� ��� Junk
data ParseResult = Fail | Success Junk

parseTerm :: String -> ParseResult
parseTerm [] = Fail
parseTerm (first:chars) =
	parseTerm' term chars
	where
		term = termByName first
		
		parseTerm' :: (Maybe Term) -> String -> ParseResult
		
		-- ���� ������ ���������� � ����� ����������
		parseTerm' (Just Variable) chars = Success chars
		
		-- ���� ������ ���������� � ����� �������, �� ����� �������
		-- ����������� ������, ��������� � ����������� ������
		parseTerm' (Just (Function arity)) chars =
			(openBracket `before` (arguments arity) `before` closeBracket) chars
			where
				openBracket = parseChar '('
				closeBracket = parseChar ')'
				
				arguments :: Arity -> String -> ParseResult		
				-- ���� ����������
				arguments 0 = Success
				-- ���� ��������
				arguments 1 = argument
				-- ����� ������ ���������
				arguments arity =
					argument `before` comma `before` (arguments (arity - 1))
					where
						comma = parseChar ','
					
				-- �������� ��� ����
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
		
		-- ���� ������ ���������� � ����-�� ������������, �� ��� �� ����
		parseTerm' Nothing _ = Fail	

isTerm :: String -> Bool
isTerm s =
	isTerm' parsed
	where
		parsed = parseTerm s
		-- ������ �������� ������ ���� ��� ������� �� ����� �� ������� ������� ������ ������
		isTerm' (Success "") = True
		isTerm' _ = False
