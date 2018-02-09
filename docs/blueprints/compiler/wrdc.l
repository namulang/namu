%{
    class Node;
    #include "bison.h"
    #include <string>
    #include <iostream>
    using namespace std;
%}

%x dquote

%%

\n {
    return teol;
}


for { return tfor; }
if { return tif; }
else { return telse; }
elif { return telif; }
def { return tdef; }
from { return tfrom; }
out { return tout; }
prop { return tprop; }
import { return timport; }
taka { return taka; }
with { return twith; }
again { return tagain; }
in { return tin; }
ret { return tret; }
retfun { return tretfun; }
retif { return tretif; }
retfor { return tretfor; }
retwith { return tretwith; }
this { return tthis; }
super { return tsuper; }
me { return tme; }
got { return tgot; }



[a-zA-Z][a-zA-Z0-9_]*   {
    yylval.strVal = strdup(yytext);
    return tidentifier;
}

<INITIAL>\" {
    BEGIN(dquote); // maximum parsing을 하기 때문에 state 관리를 해줘야 한다.
}

    <dquote>[^\"]*\" { // dquote 상태일때, <" 를 제외한 문자> + "가 붙는 경우
        BEGIN(INITIAL);
        string parsed = "\"" + string(yytext);
        yylval.strVal = strdup(parsed.c_str());
        return tstr;
    }

([1-9][0-9]*|0) {
    yylval.intVal = atoi(yytext);
    return tinteger;
}

([1-9][0-9]*.[0-9]+|0.0) {
    yylval.floatVal= atof(yytext);
    return tfloat;
}

:= { return topDefAssign; }
\+\= { return topPlusAssign; }
-= { return topMinusAssign; }
\*= { return topSquareAssign; }
\/= { return topDivideAssign; }
%= { return topModAssign; }
^= { return topPowAssign; }

\'.\' {
    yylval.charVal = yytext[1];
    return tchar;
}

true|false {
    yylval.boolVal = string(yytext) == "true" ? true : false;
    return tbool;
}

[a-za-z][a-za-z0-9_]+\( {
    string temp = yytext;
    temp = temp.substr(0, temp.size()-1);
    yylval.strVal = strdup(temp.c_str());
    unput('(');
    return tfuncname;
}

[ \t]* ;

. {
    return yytext[0];
}
<<EOF>> {
    static int cnt = 0;
    return cnt++ ? 0 : teof;
}


%%
int yywrap()
{
    return 1;
}
