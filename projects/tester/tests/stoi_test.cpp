// Example program
#include <iostream>
#include <string>
using namespace std;

int main()
{
string value = "45";
cout << "good!\n";
cout << stoi(value, 0); // << ", " << stoi(string(""), 0); this occurs error.
return 0;
}