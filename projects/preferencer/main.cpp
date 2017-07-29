#include <iostream>
#include <string>
#include "parser.hpp"

int main()
{
    using namespace NE;
    using namespace std;
    JJString string = "3+5\n";
    CharStream stream(string, 1, 1);
    HelloParserTokenManager token_manager(&stream);
    HelloParser parser(&token_manager);
    cout << parser.start();
    return 0;
}