#include <iostream>
#include <string>
#include "parser.hpp"

int main()
{
    using namespace NE;
    using namespace std;
    JJString string = 
        "class myclass\n"
        "\tkey = 3\n"
        "\tkey4 = 'c'\n"
        "\tkey3 = false";
    CharStream stream(string, 1, 1);
    PreferencerParserTokenManager token_manager(&stream);
    PreferencerParser parser(&token_manager);
    parser.configure_file();
    return 0;
}