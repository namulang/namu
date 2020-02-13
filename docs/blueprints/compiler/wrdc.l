%{
    class Node;
    #include "wrdcBison.h"
    #include <string>
    #include <iostream>
    #include <stack>
    #include <vector>
    using namespace std;

    int nowIndent = 0;
    stack<int> indentLvs;
    static const int TAB_WIDTH = 4;
    extern int nowRule;
    extern int prevRule;

    int goOutdent(char ch, int nowIndent);
    int meetEof();
    void shiftRules(int new1) {
        prevRule = nowRule;
        nowRule = new1;
    }
    int goOutdent(char ch, int nowIndent);
    int meetEof();
    void changeRule(const char* name, int new1) {
        shiftRules(new1);
        BEGIN(new1);
        cout << " ---- CHANGE RULE to " << name << "(" << new1 << ")\n";
    }
    void changePrevRule() {
        cout << " ---- CHANGE PREV RULE TO " << prevRule << "\n";
        BEGIN(prevRule);
    }
%}

%s tfile
%x dquote
%x indent
%x dedent
%x commenting

%%

for { return tfor; }
if { return tif; }
else { return telse; }
elif { return telif; }
def { return tdef; }
from { return tfrom; }
out { return tout; }
prop { return tprop; }
import { return timport; }
aka { return taka; }
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



<dedent>\/\/[^\n]* { cout << "!!!!2"; }
<indent>\/\/[^\n]* { cout << "!!!!3"; }
\/\/[^\n]* { cout << "!!!!1"; }

"/*" {
    changeRule("commenting", commenting);
}
<indent>"/*" {
    changeRule("commenting", commenting);
}
<dedent>"/*" {
    changeRule("commenting", commenting);
}
<commenting>"*/" {
    changePrevRule();
    cout << "!!!!!!!!!!!end";
}
<commenting>. { cout << "1";}
<commenting>\n { cout << "2"; }

[a-zA-Z][a-zA-Z0-9_]*   {
    yylval.strVal = strdup(yytext);
    return tidentifier;
}

<INITIAL>\" {
    changeRule("dquote", dquote); // maximum parsing을 하기 때문에 state 관리를 해줘야 한다.
}

    <dquote>[^\"\n]*\" { // dquote 상태일때, <" 를 제외한 문자> + "가 붙는 경우
        changeRule("INITIAL", INITIAL);
        string parsed = "\"" + string(yytext);
        yylval.strVal = strdup(parsed.c_str());
        return tstr;
    }

\n {
    cout << " --- enter indent rule\n";
    nowIndent = 0;
    changeRule("indent", indent);
    return teol;
}

<dedent>\n {
    nowIndent = 0;
    return teol;
}
<dedent>[ ] { nowIndent++; }
<dedent>\t {
    nowIndent = (nowIndent + TAB_WIDTH) & ~(TAB_WIDTH - 1);
}
<dedent>\0 {
    cout << "----------------------dedent: EOF!!!!!\n";
    return meetEof();
}
<dedent>. {
    char ch = yytext[0];

    int prevIndentLv = indentLvs.size() ? indentLvs.top() : 0;
    if (nowIndent < prevIndentLv)
        return goOutdent(ch, nowIndent);
    else if (nowIndent == prevIndentLv) {
        unput(ch);
        changeRule("INITIAL", INITIAL);
    }
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
\<= { return topLessEqual; }
\>\= { return topMoreEqual; }
\=\= { return topEqual; }
\=\=\= { return topRefEqual; }
\!\= { return topNotEqual; }
\!\=\= { return topNotRefEqual; }

\'.\' {
    yylval.charVal = yytext[1];
    return tchar;
}

true|false {
    yylval.boolVal = string(yytext) == "true" ? true : false;
    return tbool;
}

[a-zA-Z][a-zA-Z0-9_]+\( {
    string temp = yytext;
    temp = temp.substr(0, temp.size()-1);
    yylval.strVal = strdup(temp.c_str());
    unput('(');
    return tfuncname;
}

<indent>[ ] { nowIndent++; }
<indent>\t {
    nowIndent = (nowIndent + TAB_WIDTH) & ~(TAB_WIDTH - 1);
}
<indent>\n {
    cout << "---------------- indent newline\n";
    nowIndent = 0;
}

<indent>. {
    char ch = yytext[0];

    int prevIndentLv = indentLvs.size() ? indentLvs.top() : 0;
    cout << "  ---  indent check finish. prevIndentLv=" << prevIndentLv << " indentLvs.size()=" << indentLvs.size() << "\n";
    if (nowIndent > prevIndentLv) {
        indentLvs.push(nowIndent);
        unput(ch);
        return tindent;
    } else if (nowIndent == prevIndentLv) {
        changeRule("INITIAL", INITIAL);
        unput(ch);
    } else {
        return goOutdent(ch, nowIndent);
    }
}
<indent><<EOF>> {
    cout << "----------------------EOF!!!!!\n";
    if (goOutdent(yytext[0], nowIndent) == tdedent) {
        cout << "----------- return tdedent from EOF!\n";
        return tdedent;
    }

    cout << "----------- return meetEof()\n";
    return meetEof();
}
[ ]* {}

. {
    return yytext[0];
}
<<EOF>> {
    return meetEof();
}


%%

int meetEof() {
    static int cnt = 0;
    switch (++cnt) {
        case 0:
            cout << "-------- return teol\n";
            return teol;
        case 1:
            cout << "-------- return teof\n";
            return teof;
    }
    return 0;
}

int goOutdent(char prev, int nowIndent)
{
    int top = indentLvs.size() ? indentLvs.top() : 0;
    if (nowIndent >= top) return 0;

    indentLvs.pop();
    unput(prev);
    for (int n=0; n < nowIndent ;n++)
        unput(' ');
    unput('\n');
    changeRule("dedent", dedent);
    cout << " ----- dedent: pop! now " << indentLvs.size() << " dedentLv left. \n";
    return tdedent;
}

int nowRule = INITIAL;
int prevRule = INITIAL;
int yywrap()
{
    return 1;
}
