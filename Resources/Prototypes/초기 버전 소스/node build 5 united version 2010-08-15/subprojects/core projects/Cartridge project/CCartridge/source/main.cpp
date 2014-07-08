#include <iostream>
using namespace std;

#include "CCartridge.hpp"
#include <string.h>
#include <tchar.h>

int main(int argc, TCHAR* argv[])
{
	cout << "argc count is :" << (argc - 1);
	
	for (int n=1; n < argc ;n++)
	{
		cout << "\n" << (n) << "th file path is:\t" << argv[n];
	}

	cout << "\n file end!";

	cout << "\n" << newstr;
	int dummy;
	cin >> dummy;

	return EXIT_SUCCESS;
}