#include <cassert>

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <set>
#include <string>

// переменная - это имя переменной - символ
typedef char Variable;

// использование переменной, либо с отрицанием, либо без
class VariableUsing
{
public:
	bool Negation;
	Variable Var;

	VariableUsing(const Variable& var) : Negation(false), Var(var) {}

	VariableUsing(const Variable& var, const bool negation) : Negation(negation), Var(var) {}
};

inline VariableUsing operator !(const VariableUsing& var)
{
	return VariableUsing(var.Var, !var.Negation);
}

inline bool operator <(const VariableUsing& a, const VariableUsing& b)
{
	return (a.Var < b.Var) || (a.Var == b.Var) && (a.Negation > b.Negation);
}

inline bool operator ==(const VariableUsing& a, const VariableUsing& b)
{
	return (a.Var == b.Var) && (a.Negation == b.Negation);
}

// элементарная конъюнкция - неупорядоченный набор переменных, возможно с отрицанием
typedef std::set<VariableUsing> Conjunction;

// днф - дизъюнкция набора элементарных конъюнкций - неупорядоченный набор конъюнкций
typedef std::set<Conjunction> DNF;

// исключение парсера
class ParseException : public std::runtime_error
{
public:
	ParseException(const std::string& message) : std::runtime_error(message) {}
};

// класс, умеющий парсить строку в ДНФ
// синтакис строки:
//	 дизъюнкция, это набор конъюнкций, разделённых символом "|"
//   конъюнкция - это набор имён переменных записанных подряд
//   имя переменной - это строчная буква латинского алфавита (a-z), возможно предварённая символом "!" - отрицание
//   пробелы игнорируются
class Parser
{
private:
	size_t position;
	std::string text;

	bool isAlpha(const char c) const
	{
		return c >= 'a' && c <= 'z';
	}

	bool hasChar()
	{
		// Пропускаем пробелы
		while(position < text.size() && text[position] == ' ')
			++position;

		return position < text.size();
	}

	char nextChar()
	{
		if(hasChar())
		{
			return text[position];
		}
		else
		{
			throw ParseException("unexpected end of string");
		}
	}

	bool nextChar(const char eta)
	{
		return nextChar() == eta;
	}

	char getChar()
	{
		char c = nextChar();
		++position;
		return c;
	}

	VariableUsing getVar();

public:
	Parser(const std::string& text_) : position(0), text(text_) {}

	DNF ParseDNF();
};

DNF Parser::ParseDNF()
{
	DNF ans;
	Conjunction currentConjunction;
	
	while(hasChar())
	{
		char c = nextChar();

		if(c == '|')
		{
			getChar();
			// добавляем текущую конъюнкцию к днф и обнуляем её
			ans.insert(currentConjunction);
			currentConjunction = Conjunction();
		}
		else
		{
			currentConjunction.insert(getVar());
		}
	}

	ans.insert(currentConjunction);

	return ans;
}

VariableUsing Parser::getVar()
{
	bool negation = false;

	if(nextChar('!'))
	{
		negation = true;
		getChar();
	}

	char v = getChar();

	if(isAlpha(v))
	{
		return VariableUsing(v, negation);
	}
	else
	{
		throw ParseException("Unexpected character.");
	}
}

std::ostream& operator <<(std::ostream& os, const VariableUsing& var)
{
	if(var.Negation)
	{
		os << '!';
	}

	os << var.Var;

	return os;
}

std::ostream& operator <<(std::ostream& os, const Conjunction& conj)
{
	for(Conjunction::const_iterator it = conj.begin(); it != conj.end(); ++it)
		os << *it;

	if(conj.empty())
		os << "1";

	return os;
}

std::ostream& operator <<(std::ostream& os, const DNF& dnf)
{
	size_t i = 0;

	for(DNF::const_iterator it = dnf.begin(); it != dnf.end(); ++it, ++i)
		os << (i > 0 ? " | " : "") << *it;

	if(dnf.empty())
		os << "0";

	return os;
}

bool NullConjunction(const Conjunction& c)
{
	for(Conjunction::const_iterator x = c.begin(); x != c.end(); ++x)
		if(c.count(!*x))
			return true;

	return false;
}

bool Contains(const Conjunction& a, const Conjunction& b)
{
	for(Conjunction::const_iterator it = b.begin(); it != b.end(); ++it)
		if(!a.count(*it))
			return false;

	return true;
}

// http://www.intuit.ru/department/ds/discrmath/4/3.html
DNF Blake(const DNF& orig)
{
	DNF b = orig;

	// 1 шаг, склеивание
	for(DNF::const_iterator c1 = orig.begin(); c1 != orig.end(); ++c1)
		for(DNF::const_iterator c2 = orig.begin(); c2 != orig.end(); ++c2)
		{
			// нашли пару конъюнкций
			// ищём пару переменных x и !x

			for(Conjunction::const_iterator x = c1->begin(); x != c1->end(); ++x)
			{
				// если во второй конъюнкции есть противоположная переменная...
				if(c2->count(!*x))
				{
					// склеиваем их и удаляем пару противоположных переменных
					Conjunction s = *c1;
					s.insert(c2->begin(), c2->end());
					s.erase(*x);
					s.erase(!*x);

					// если результат склейки не равен тождественно нулю, то добавляем в ответ
					if(!NullConjunction(s))
						b.insert(s);
				}
			}
		}

	// второй шаг, поглощение
	DNF old = b;
	
	for(DNF::const_iterator it = old.begin(); it != old.end(); ++it)
	{
		// удаляем из b все конъюнкции, которые будут поглощены *it
		DNF tmp;

		for(DNF::const_iterator jt = b.begin(); jt != b.end(); ++jt)
			if(*it == *jt || !Contains(*jt, *it))
				tmp.insert(*jt);

		b = tmp;
	}

	return b;
}

int main()
{
	std::string text;

	std::cin >> text;
	
	try
	{
		Parser parser(text);

		DNF f = parser.ParseDNF();

		std::cout << "Original DNF: " << f << std::endl;

		DNF newf = f;

		do
		{
			f = newf;
			newf = Blake(f);
		}
		while(f != newf);

		std::cout << "Blake's DNF: " << f << std::endl;
	}
	catch(const ParseException& e)
	{
		std::cout << "ParseException: " << std::string(e.what()) << std::endl;
	}

	return 0;
}