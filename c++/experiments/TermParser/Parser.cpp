#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

// исключение, выбрасываемое если данная на вход строка не является термом
class NotATerm : public std::invalid_argument
{
public:
	NotATerm(const std::string& message) : std::invalid_argument(message)
	{
	}
};

// класс, умеющий проверять, является ли произвольная строка термом, и вычислять значение этого терма
// используется метод рекурсивного спуска, которому нас учил Дрозд на первом или втором курсе
template<typename Type>
class Parser
{
public: // types
	// определяем тип Function - функция, которая получает вектор аргументов типа Type и возвращает значение типа Type
	typedef Type (*Function)(const std::vector<Type>&);
	// константа
	typedef Type Constant;

private: // fields
	std::map<char, Function> functions_;
	std::map<char, Constant> constants_;
	// Текст, которые анализируется
	std::string text;
	// номер текущего просматриваемого символа
	size_t position;

private: // methods
	// прочитать с входа символ и вернуть его
	char parseChar()
	{
		++position;
		if(position <= text.size())
		{
			return text[position - 1];
		}
		else
		{
			throw NotATerm("unexpected end of input");
		}
	}

	// прочитать с входа символ и убедиться что он совпадает с заданным
	void parseChar(const char expected)
	{
		const char real = parseChar();

		if(real != expected)
		{
			std::stringstream err;
			err<<"'"<<expected<<"', but '"<<real<<"' found";
			throw NotATerm(err.str());
		}
	}

	// прочитать все аргументы с входа, а также открывающую и закрывающую скобки
	std::vector<Type> parseArguments()
	{
		parseChar('(');
		std::vector<Type> arguments;
		char delimiter;
		
		// читаем аргументы, пока между ними запятая
		do
		{
			arguments.push_back(parseTerm());
			delimiter = parseChar();
		}
		while(delimiter == ',');

		// запятые кончились, это должно быть закрывающая скобка
		if(delimiter == ')')
		{
			return arguments;
		}
		else
		{
			throw NotATerm(std::string("',' or ')' expected, but '") + delimiter + "' found");
		}
	}

	// прочитать со входа терм и вернуть значение
	Type parseTerm()
	{
		// прочитать первый символ
		char name = parseChar();

		if(functions_.count(name) > 0)
		{
			// если это функция, то читаем аргументы
			const std::vector<Type> arguments = parseArguments();

			return (*functions_[name])(arguments);
		}
		else if(constants_.count(name) > 0)
		{
			// если это константа
			return constants_[name];
		}
		else
		{
			throw NotATerm(std::string("Unexpected symbol: ") + name);
		}
	}

public:
	Parser(const std::map<char, Function>& functions, const std::map<char, Constant>& constants, const std::string& expression) :
		functions_(functions), constants_(constants), text(expression), position(0)
	{

	}
	
	Type Parse()
	{
		try
		{
			Type result = parseTerm();

			if(position == text.size())
			{
				return result;
			}
			else
			{
				throw NotATerm("junk after term");
			}
		}
		catch(const NotATerm& ex)
		{
			std::stringstream err;
			err<<ex.what()<<" "<<"[position="<<position<<"]";

			throw NotATerm(err.str());
		}
	}
};

// ПРИМЕРЫ ФУНКЦИЙ

// f - функция двух переменных
// в данном случае она возвращает сумму своих двух аргументов
double f(const std::vector<double>& arguments)
{
	if(arguments.size() == 2)
	{
		// аргументы нумеруются с 0
		return arguments[0] + arguments[1];
	}
	else
	{
		std::stringstream err;
		err<<"function 'f' can process 2 arguments, but "<<arguments.size()<<" given!";

		throw NotATerm(err.str());
	}
}

// функция одной переменной, меняющая знак
double n(const std::vector<double>& arguments)
{
	if(arguments.size() == 1)
	{
		return -arguments[0];
	}
	else
	{
		std::stringstream err;
		err<<"function 'n' can process 1 arguments, but "<<arguments.size()<<" given!";

		throw NotATerm(err.str());
	}
}

// p - функция трёх переменных
// в данном случае она возвращает произведение своих трёх аргументов
double p(const std::vector<double>& arguments)
{
	if(arguments.size() == 3)
	{
		// аргументы нумеруются с 0
		return arguments[0] * arguments[1] * arguments[2];
	}
	else
	{
		std::stringstream err;
		err<<"function 'p' can process 3 arguments, but "<<arguments.size()<<" given!";

		throw NotATerm(err.str());
	}
}

int main()
{
	typedef Parser<double> myParser;

	// набор используемых функций
	std::map<char, myParser::Function> functions;
	functions['f'] = &f;
	// по аналогии можно написать другие функции g, h, которые что-то будут делать
	functions['+'] = &f;
	functions['n'] = &n;
	functions['p'] = &p;
	functions['*'] = &p;
	
	// набор используемых констант
	std::map<char, myParser::Constant> constants;
	constants['x'] = 1.0;
	constants['1'] = 1.0;
	constants['y'] = 2.0;
	constants['2'] = 2.0;
	constants['z'] = 3.0;
	constants['3'] = 3.0;
	constants['u'] = 4.0;
	constants['4'] = 4.0;
	constants['v'] = 5.0;
	constants['5'] = 5.0;

	std::string input;

	// читаем ввод пользователя
	std::cin >> input;

	// пытаемся вычислить значение терма
	try
	{
		const double result = myParser(functions, constants, input).Parse();
		std::cout<<"Result: "<<result<<std::endl;
	}
	catch(const NotATerm& ex)
	{
		// если не получилось, то выводим соответствующее сообщение
		std::cout<<"It isn't a term ("<<ex.what()<<")"<<std::endl;
	}

	return 0;
}
