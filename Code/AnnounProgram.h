#ifndef PROGRAMM
#define PROGRAMM

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h>

using namespace std;

class Translator
{
public:
	Translator();
	virtual ~Translator();
	void FromFile(Translator&);
	void FromFile(Translator&, string);
	void FromConsole(Translator&);
	void Translate(Translator&);
	string GetType(string);
	friend ostream& operator<<(std::ostream&, const Translator&);

	void SetOneString(string line) { StringsInFile.push_back(line); }

private:
	vector<string> StringsInFile;
	map<string, int> dictionary = { {"Dim", 1}, {"ElseIf" , 2}, {"If", 3}, {"AND", 4}, {"OR", 5}, {"REM", 6}, {"Con", 7}, {"Wri", 8},
		{"=", 9}, {"Then", 10}, {"End", 11}, {"For", 12}, {"Next", 13} };
	map<string, int> types = { {"Integer", 1}, {"Boolean", 2}, {"Char", 3}, {"Double", 4}, {"Long", 5}, {"String", 6}, {"Short", 7} };
};

class Starter
{
public:
	Starter();
	~Starter();
	bool StartTranslate(Translator&, int);
	void StartCode();
private:

};

class Visual : protected Translator
{
public:
	Visual();
	virtual ~Visual();
	void PrintElementaryCode(Translator&);
	void PrintUltimate();
private:

};

#endif