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
    void changeRule(const char* name, int new1) {
        if (nowRule == new1) return;

        shiftRules(new1);
        BEGIN(new1);
        cout << " ---- CHANGE RULE to " << name << "(" << new1 << ")\n";
    }
    void changePrevRule() {
        cout << " ---- CHANGE PREV RULE TO " << prevRule << "\n";
        BEGIN(prevRule);
    }
%}

%x dquote
%s tfile
%x indent
%x dedent
%x commenting
%x arraytyping

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
(_)*@ctor {
    yylval.strVal = strdup(yytext);
    return tfctor;
}
(_)*@dtor { return tfdtor; }
(_)*@res { return tfres; }
(_)*@warn { return tfwarn; }
(_)*@err { return tferr; }

true|false {
    yylval.boolVal = string(yytext) == "true" ? true : false;
    return tbool;
}

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






[a-zA-Z][a-zA-Z0-9_]*\[ {
    string temp = yytext;
    changeRule("arraytyping", arraytyping);

    unput('[');
    temp = temp.substr(0, temp.size()-1);
    yylval.strVal = strdup(temp.c_str());
    return tnormalId;
}

<arraytyping>\[ {
    cout << "----------lex: found '[' \n";
    return yytext[0];
}
<arraytyping>\]\[ {
    unput('[');
    return yytext[0];
}
<arraytyping>\] {
    changePrevRule();
    cout << "----------lex: found ']' \n";
    return yytext[0];
}
<arraytyping>[a-zA-Z0-9_]+\] {
    string temp = yytext;
    temp = temp.substr(0, temp.size()-1);
    unput(']');
    yylval.strVal = strdup(temp.c_str());
    cout << "----------lex: tnormalId is " << yylval.strVal << " ---- \n";
    return tnormalId;
}



[a-zA-Z][a-zA-Z0-9_]*   {
    yylval.strVal = strdup(yytext);
    return tnormalId;
}

(_$|_|$)[a-zA-Z0-9_]+ {
    // Accessed 컨셉:
    //  배경:
    //      * accessed란 식별자 정의시, 그 앞에 protected인지 static인지 속성을 지정하는 것을 말한다.
    //      * 이때 이 accessed가 올바르게 작성된것인지 판단을 lexer에서 하는지, parser에서 하는지를 구분하고자 한다.
    //
    //  해결:
    //      * lex에서는 accessed가 올 수 있는자리다... 라는 것 까지만 판단한다.
    //      *  이를테면 모든 시나리오를 고려했을때 해당 lexer 룰의 accessed가 와도 되는 케이스가 1개라도 존재한다면
    //      *  lex에서는 accessed가 올 수 있다는 걸 rule에 포함할 것이다.
    //      * 정말로 accessed가 올바르게 작성되었는가는 파서가 판단한다.
    //      *  왜냐하면 이것을 정확하게 알기 위해서는 파서가 앞 뒤의 문맥을 보고 판단을 해야 하기 때문이다.
    //
    //  결론:
    //      * lexer는 문맥을 보지 못한다. 해당 rule에 accessed가 올 수 있는 1가지의 시나리오라도 존재한다면 rule에 포함한다.
    //      * 파서는 문맥을 볼 수 있으므로, lexer가 건내준 accessed가 올바른 것인지 최종 판단한다.

    yylval.strVal = strdup(yytext);
    return taccessedId;
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
<dedent>. {
    char ch = yytext[0];

    int prevIndentLv = indentLvs.size() ? indentLvs.top() : 0;
    cout << "  ---  ch=" << ch << "(" << (int) ch << ") dedent check finish. prevIndentLv=" << prevIndentLv << " indentLvs.size()=" << indentLvs.size() << "\n";
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
\?\. { return topSafeNavi; }
\.\. { return topSeq; }
\=\> { return topRedirect; }

\'.\' {
    yylval.charVal = yytext[1];
    return tchar;
}

(_)[a-zA-Z0-9_]+\( {
    string temp = yytext;
    temp = temp.substr(0, temp.size()-1);
    yylval.strVal = strdup(temp.c_str());
    unput('(');
    return taccessedFuncname;
}

[a-zA-Z][a-zA-Z0-9_]*\( {
    string temp = yytext;
    temp = temp.substr(0, temp.size()-1);
    yylval.strVal = strdup(temp.c_str());
    unput('(');
    return tnormalFuncname;
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

[ ]* {
}

. {
    return yytext[0];
}

<<EOF>> {
    return meetEof();
}


%%

int meetEof() {
    static int cnt = 0;
    cout << "----------- meetEOF(" << cnt << ")\n";
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
