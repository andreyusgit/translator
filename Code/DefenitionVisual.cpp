#include "AnnounProgram.h"

Visual::Visual()
{
}

Visual::~Visual()
{
}

void Visual::PrintElementaryCode(Translator& code)
{
    cout << "\nThe starting code was:\n\n------------------------------------------------------------------\n";
	cout << code;
    cout << "\n------------------------------------------------------------------\n";
}
void Visual::PrintUltimate()
{
    cout << "\nAfter translating we have this code:\n\n------------------------------------------------------------------\n";
    std::string line;
    std::ifstream in(".\\result.cpp");
    if (in.is_open())
    {
        while (getline(in, line))
        {
            std::cout << line << std::endl;
        }
    }
    in.close();
    cout << "\n------------------------------------------------------------------\n";
}