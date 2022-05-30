#include "AnnounProgram.h"



int main()
{
	int res; 
	bool correctWork = false;
	cout << "How you want translate? \n1 - From file \"code.txt\"\n2 - From anouther file\n3 - From console\n- recommend from \"code.txt\" -\n0 - if it is your second start\nYour choice: ";
	cin >> res;
	Starter program;
	Translator first;
	Visual run;
	if (res == 0) {
		program.StartCode();
		return 0;
	}
	else {
		while (!correctWork) {
			correctWork = program.StartTranslate(first, res);
		}
	}
	correctWork = false;
	while (!correctWork) {
		cout << "\n-How many information you want to see?\n1 - just run the translated code\n" <<
			"2 - just output the final code\n3 - output the final code and run translated code\n4 - output the starting code, translated and run it\nYour choice: ";
		cin >> res;
		switch (res)
		{
		case 1: 
		{
			program.StartCode();
			correctWork = true;
			break;
		}
		case 2:
		{
			run.PrintUltimate();
			correctWork = true;
			break;
		}
		case 3:
		{
			run.PrintUltimate();
			cout << "\nSorry, for correct running - start program again and choice \"0\"\n";
			correctWork = true;
			break;
		}
		case 4:
		{
			run.PrintElementaryCode(first);
			run.PrintUltimate();
			cout << "\nSorry, for correct running - start program again and choice \"0\"\n";
			correctWork = true;
			break;
		}
		default:
			cout << "\n *=*you enter wrong number, try again*=*\n";
			break;
		}
	}
}
