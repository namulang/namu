#include <iostream>
#include <string>
class Node;
#include "wrdcBison.h"
#include "wrdcNode.hpp"
int yylex();
extern int yylineno;
extern char* yytext;
int yyparse();

extern FILE *yyin, *yyout;
extern File* parsed;
bool USE_OP = false;

int main(int argc, char* argv[])
{
    using namespace std;

    cout    << "\n"
            << " 2020 @ Worldlang interpreter. prototype ver. by kniz\n"
            << " it's on github, github.com/kniz/worldlang with LGPL licensed.\n"
            << " " << argv[0] << " [<option>] <filename> [\n"
            << " options:\n"
            << " \t-d\tuse Debug mode. prints all logs when it compiles.\n"
            << " \t-op\tprint operator precedence by paranthesis.\n";

    if (argc > 1)
    {
        for (int n=1; n < argc ;n++) {
            if (argv[n] == string("-d")) {
                cout << " - use debug mode. \n";
#ifdef YYDEBUG
                yydebug = 1;
#endif
            } else if (argv[n] == string("-op")) {
                USE_OP = true;
            } else {
                yyin = fopen(argv[n], "r");
                cout << " opening " << argv[n] << " file...\n";
            }
        }
    }
    else
        cout << " <press ctrl + c or d if you want to quit>\n";

    int res = yyparse();
    if (parsed)
        cout << parsed->print();
    if (res)
        cout << " FAILED!\n";
    return res;
}
