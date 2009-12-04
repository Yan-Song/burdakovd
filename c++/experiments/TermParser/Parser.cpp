#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

// ����������, ������������� ���� ������ �� ���� ������ �� �������� ������
class NotATerm : public std::invalid_argument
{
public:
	NotATerm(const std::string& message) : std::invalid_argument(message)
	{
	}
};

// �����, ������� ���������, �������� �� ������������ ������ ������, � ��������� �������� ����� �����
// ������������ ����� ������������ ������, �������� ��� ���� ����� �� ������ ��� ������ �����
template<typename Type>
class Parser
{
public: // types
	// ���������� ��� Function - �������, ������� �������� ������ ���������� ���� Type � ���������� �������� ���� Type
	typedef Type (*Function)(const std::vector<Type>&);
	// ���������
	typedef Type Constant;

private: // fields
	std::map<char, Function> functions_;
	std::map<char, Constant> constants_;
	// �����, ������� �������������
	std::string text;
	// ����� �������� ���������������� �������
	size_t position;

private: // methods
	// ��������� � ����� ������ � ������� ���
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

	// ��������� � ����� ������ � ��������� ��� �� ��������� � ��������
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

	// ��������� ��� ��������� � �����, � ����� ����������� � ����������� ������
	std::vector<Type> parseArguments()
	{
		parseChar('(');
		std::vector<Type> arguments;
		char delimiter;
		
		// ������ ���������, ���� ����� ���� �������
		do
		{
			arguments.push_back(parseTerm());
			delimiter = parseChar();
		}
		while(delimiter == ',');

		// ������� ���������, ��� ������ ���� ����������� ������
		if(delimiter == ')')
		{
			return arguments;
		}
		else
		{
			throw NotATerm(std::string("',' or ')' expected, but '") + delimiter + "' found");
		}
	}

	// ��������� �� ����� ���� � ������� ��������
	Type parseTerm()
	{
		// ��������� ������ ������
		char name = parseChar();

		if(functions_.count(name) > 0)
		{
			// ���� ��� �������, �� ������ ���������
			const std::vector<Type> arguments = parseArguments();

			return (*functions_[name])(arguments);
		}
		else if(constants_.count(name) > 0)
		{
			// ���� ��� ���������
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

// ������� �������

// f - ������� ���� ����������
// � ������ ������ ��� ���������� ����� ����� ���� ����������
double f(const std::vector<double>& arguments)
{
	if(arguments.size() == 2)
	{
		// ��������� ���������� � 0
		return arguments[0] + arguments[1];
	}
	else
	{
		std::stringstream err;
		err<<"function 'f' can process 2 arguments, but "<<arguments.size()<<" given!";

		throw NotATerm(err.str());
	}
}

// ������� ����� ����������, �������� ����
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

// p - ������� ��� ����������
// � ������ ������ ��� ���������� ������������ ����� ��� ����������
double p(const std::vector<double>& arguments)
{
	if(arguments.size() == 3)
	{
		// ��������� ���������� � 0
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

	// ����� ������������ �������
	std::map<char, myParser::Function> functions;
	functions['f'] = &f;
	// �� �������� ����� �������� ������ ������� g, h, ������� ���-�� ����� ������
	functions['+'] = &f;
	functions['n'] = &n;
	functions['p'] = &p;
	functions['*'] = &p;
	
	// ����� ������������ ��������
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

	// ������ ���� ������������
	std::cin >> input;

	// �������� ��������� �������� �����
	try
	{
		const double result = myParser(functions, constants, input).Parse();
		std::cout<<"Result: "<<result<<std::endl;
	}
	catch(const NotATerm& ex)
	{
		// ���� �� ����������, �� ������� ��������������� ���������
		std::cout<<"It isn't a term ("<<ex.what()<<")"<<std::endl;
	}

	return 0;
}
