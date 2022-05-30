#include "AnnounProgram.h"
#include "result.cpp"


Starter::Starter() {

}
Starter::~Starter() {

}
bool Starter::StartTranslate(Translator& first, int check) {

	switch (check)
	{
	case 1: {
		first.FromFile(first);
		break;
	}
	case 2: {
		string path;
		cout << "Enter full file path: ";
		cin >> path;
		first.FromFile(first, path);
		break;
	}
	case 3: {
		first.FromConsole(first);
		break;
	}
	default:
		cout << "\n *=*you enter wrong number, try again*=*\n";
		return false;
		break;
	}
	first.Translate(first);
	return true;
}

void Starter::StartCode() {
	cout << "\n------------------------------------------------------------------\n";
	code();
}