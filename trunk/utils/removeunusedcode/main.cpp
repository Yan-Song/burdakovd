#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>

using namespace std;

bool isTokenChar(int c) {
	return isalpha(c) || isdigit(c) || (c == '_') || (c == '$');
}

string getDefineName(string s) {
    string name = "";
	int i = 0;
	while (!isspace(s[i])) ++i;
	while (isspace(s[i])) ++i;
	while ((i < s.length()) && !isspace(s[i]) && (s[i] != '(')) name += s[i++];
	return name;
}

string getTypedefName(string s) {
    string name = "";
    int i = s.length() - 1;
    while (true) {
    	if (s[i] == ']') {
    		while (s[i] != '[') --i;
    	} else if (isTokenChar(s[i])) break;
    	--i;
    }
    while (isTokenChar(s[i])) name = (char)s[i--] + name;
	return name;
}

string getConstName(string s) {
    string name = "";
    int i = s.find("=");
    while (true) {
    	if (s[i] == ']') {
    		while (s[i] != '[') --i;
    	} else if (isTokenChar(s[i])) break;
    	--i;
    }
    while (isTokenChar(s[i])) name = s[i--] + name;
	return name;
}

bool isEmptyLine(string s)
{
	for(int i=0; i<s.size(); ++i)
		if(s[i] != ' ' && s[i] != '\t')
			return false;

	return true;
}

int main() {

	freopen("e:\\in.txt", "r", stdin);
	freopen("e:\\out.cpp", "w", stdout);


	vector<string> code;
	string s;
	while (getline(cin, s)) code.push_back(s);

	bool bAssert = false, bOutput = false;
	
	vector<string> not_cleared;

	do
	{
		int prevEmptyLines = 0;
		not_cleared = code;
		vector<string> temp;
		for (int i = 0; i < code.size(); ) {
			vector<string> tcode;

			for(; i<code.size() && !isEmptyLine(code[i]); ++i)
			{
				bool ba = false, bo = false;
				string w = "";
				for (int k = 0; k <= code[i].length(); ++k) {
					if (isTokenChar(code[i][k]))
						w += code[i][k];
					else if (w != "") {
						if (w == "assert") ba = true;
						if ((w == "cout") || (w == "cerr") || (w == "printf")) bo = true;
						w = "";
					}
				}
				
				if ((code[i].find("#define") == 0) ||
					(code[i].find("typedef") == 0) ||
					(code[i].find("const") == 0)) {
					string name = "";
					if (code[i].find("#define") != string::npos) name = getDefineName(code[i]);
					else if (code[i].find("typedef") != string::npos) name = getTypedefName(code[i]);
					else name = getConstName(code[i]);
					bool used = false;
					for (int j = i + 1; !used && (j < code.size()); ++j) {
						string w = "";
						for (int k = 0; !used && (k <= code[j].length()); ++k) {
							if (isalpha(code[j][k]) || isdigit(code[j][k]) || (code[j][k] == '_') || (code[j][k] == '$'))
								w += code[j][k];
							else if (w != "") {
								if (w == name) used = true;
								w = "";
							}
						}
					}
					if (used) tcode.push_back(code[i]), bAssert |= ba, bOutput |= bo;
				} else tcode.push_back(code[i]), bAssert |= ba, bOutput |= bo;
			}

			int curEmptyLines = 0;
			// empty
			for(; i<code.size() && isEmptyLine(code[i]); ++i)
				++curEmptyLines;

			if(tcode.empty())
				prevEmptyLines = max(prevEmptyLines, curEmptyLines);
			else
			{
				for(int j=0; j<prevEmptyLines; ++j)
					temp.push_back("");

				for(int j=0; j<tcode.size(); ++j)
					temp.push_back(tcode[j]);

				prevEmptyLines = curEmptyLines;
			}
			
		}
		code = temp;
		temp.clear();
	}
	while(code != not_cleared);

	for(int i=0; i<code.size(); ++i)
		cout<<code[i]<<endl;

	if (bAssert) cerr << "Warning: Some assert's are used" << endl;
	if (bOutput) cerr << "Warning: Display output is used." << endl;

	return 0;
}
