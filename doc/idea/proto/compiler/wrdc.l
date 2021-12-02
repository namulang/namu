%{

// #1 INITIAL은 indent를 체크하는 state여야 한다.
// #2 dedent 후 \n이 온다.
// #3 엔터 한번에 2개 이상의 dedent를 한 경우도 역시 dedent \n 을 매번 해준다.
// #4 eof를 만나면 별다른 처리 없이 return 0 하면 된다.
// #5 changeRule을 없앨 방법을 찾아보자:
//    1. 내장된 매크로를 찾아서 있으면 사용한다.
//    2. 로직적으로 필요없게 만들어본다.

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

int goOutdent(char ch);
int meetEof();
void shiftRules(int new1) {
    prevRule = nowRule;
    nowRule = new1;
}
void changeRule(const char* name, int new1) {
    if (nowRule == new1) return;

    shiftRules(new1);
    BEGIN(new1);
    if (yydebug)
        cout << " ---- CHANGE RULE to " << name << "(" << new1 << ")\n";
}
void changePrevRule() {
    if (yydebug)
        cout << " ---- CHANGE PREV RULE TO " << prevRule << "\n";
    BEGIN(prevRule);
}
%}

%x dquote
%x normal
%x dedent
%x commenting
%x arraytyping

%%

<normal>switch { return tswitch; }
<normal>pack { return tpack; }
<normal>for { return tfor; }
<normal>if { return tif; }
<normal>else { return telse; }
<normal>elif { return telif; }
<normal>"def"[\(]* {
    string temp = yytext;
    if(temp[temp.size()-1] == '(') {
        temp = temp.substr(0, temp.size()-1);
        unput('(');
    }

    yylval.strVal = strdup(temp.c_str());
    return tdef;
}
<normal>from { return tfrom; }
<normal>"prop"[\(]* {
    string temp = yytext;
    if(temp[temp.size()-1] == '(') {
        temp = temp.substr(0, temp.size()-1);
        unput('(');
    }

    yylval.strVal = strdup(temp.c_str());
    return tprop;
}
<normal>null { return tnull; }
<normal>import { return timport; }
<normal>aka { return taka; }
<normal>with { return twith; }
<normal>next { return tnext; }
<normal>in { return tin; }
<normal>ret { return tret; }
<normal>as { return tas; }
<normal>return { return treturn; }
<normal>(_)*@set {
    yylval.strVal = strdup(yytext);
    return tfset;
}
<normal>(_)*@get {
    yylval.strVal = strdup(yytext);
    return tfget;
}
<normal>(_)*@ctor {
    yylval.strVal = strdup(yytext);
    return tfctor;
}
<normal>(_)*@dtor {
    yylval.strVal = strdup(yytext);
    return tfdtor;
}

<normal>true|false {
    yylval.boolVal = string(yytext) == "true" ? true : false;
    return tbool;
}

<normal,INITIAL,dedent>\/\/[^\n]*\n {
    cout << "consume single-line comment\n";
    nowIndent = 0;
    if(YY_START == normal) {
        return teol;
    }
}

"/*" {
    changeRule("commenting", commenting);
}
<INITIAL,dedent>"/*" {
    changeRule("commenting", commenting);
}
<commenting>"*/" {
    changePrevRule();
    if(yydebug)
        cout << "!!!!!!!!!!!end";
}
<commenting>. { if(yydebug) cout << "1";}
<commenting>\n { if(yydebug) cout << "2"; }






<normal>[a-zA-Z][a-zA-Z0-9_]*\{ {
    string temp = yytext;
    changeRule("arraytyping", arraytyping);

    unput('{');
    temp = temp.substr(0, temp.size()-1);
    yylval.strVal = strdup(temp.c_str());
    return tconName;
}

<arraytyping>\{ {
    if(yydebug)
        cout << "----------lex: found '{' \n";
    return yytext[0];
}
<arraytyping>\}\{ {
    unput('{');
    return yytext[0];
}
<arraytyping>\} {
    changePrevRule();
    if(yydebug)
        cout << "----------lex: found '}' \n";
    return yytext[0];
}
<arraytyping>[a-zA-Z0-9_]+\} {
    string temp = yytext;
    temp = temp.substr(0, temp.size()-1);
    unput('}');
    yylval.strVal = strdup(temp.c_str());
    if(yydebug)
        cout << "----------lex: tnormalId is " << yylval.strVal << " ---- \n";
    return tnormalId;
}

<normal>[a-zA-Z][a-zA-Z0-9_]*   {
   yylval.strVal = strdup(yytext);
    return tnormalId;
}

<normal>(_$|_|$)[a-zA-Z0-9_]+ {
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

<normal>\' {
    changeRule("dquote", dquote); // maximum parsing을 하기 때문에 state 관리를 해줘야 한다.
}

    <dquote>[^\'\n]*\' { // dquote 상태일때, <" 를 제외한 문자> + "가 붙는 경우
        changeRule("normal", normal);
        string parsed = "\'" + string(yytext);
        yylval.strVal = strdup(parsed.c_str());
        return tstr;
    }

<normal>\n {
    if(yydebug)
        cout << " --- enter indent rule\n";
    nowIndent = 0;
    changeRule("INITIAL", INITIAL);
    return teol;
}


<normal>([1-9][0-9]*|0) {
    yylval.floatVal = atof(yytext);
    return tnum;
}

<normal>([1-9][0-9]*.[0-9]+|0.[0-9]+) {
    yylval.floatVal= atof(yytext);
    return tnum;
}

<normal>:= { return topDefAssign; }
<normal>\+\= { return topPlusAssign; }
<normal>-= { return topMinusAssign; }
<normal>\*= { return topSquareAssign; }
<normal>\/= { return topDivideAssign; }
<normal>%= { return topModAssign; }
<normal>^= { return topPowAssign; }
<normal>\<= { return topLessEqual; }
<normal>\>\= { return topMoreEqual; }
<normal>\=\= { return topEqual; }
<normal>\=\=\= { return topRefEqual; }
<normal>\!\= { return topNotEqual; }
<normal>\!\=\= { return topNotRefEqual; }
<normal>\?\. { return topSafeNavi; }
<normal>\.\. { return topSeq; }
<normal>\+\+ { return topUplus; }
<normal>\-\- { return topUminus; }

<normal>\'.\' {
    yylval.charVal = yytext[1];
    return tchar;
}

<INITIAL>[ ] {
    nowIndent++;
    cout << " nowIndent = " << nowIndent << "\n";
}
<INITIAL>\t {
    nowIndent = (nowIndent + TAB_WIDTH) & ~(TAB_WIDTH - 1);
    cout << " nowIndent = " << nowIndent << "\n";
}
<INITIAL>\n {
    nowIndent = 0;
    if(yydebug)
        cout << " nowIndent = " << nowIndent << " newline!\n";
}
<dedent>\n { return teol; }
<INITIAL,dedent>. {
    char ch = yytext[0];

    int prevIndentLv = indentLvs.size() ? indentLvs.top() : 0;
    if(yydebug)
        cout << "  ---  indent check finish. ch=" << ch << "(" << (int) ch << ") prevIndentLv=" << prevIndentLv << " indentLvs.size()=" << indentLvs.size() << "\n";
    if (ch == 0) {
    } else if (nowIndent > prevIndentLv) {
        indentLvs.push(nowIndent);
        unput(ch);
        changeRule("normal", normal);
        return tindent;

    } else if (nowIndent == prevIndentLv) {
        changeRule("normal", normal);
        unput(ch);
    } else {
        return goOutdent(ch);
    }
}

<INITIAL,dedent><<EOF>> {
    if(yydebug)
        cout << "----------------------EOF!!!!!\n";
    if (goOutdent(yytext[0]) == tdedent) {
        if(yydebug)
            cout << "----------- return tdedent from EOF!\n";
        return tdedent;
    }

    if(yydebug)
        cout << "----------- return meetEof()\n";
    return meetEof();
}

<normal>[ ]* {
}

<normal>. {
    return yytext[0];
}

<normal><<EOF>> {
    return meetEof();
}


%%

int meetEof() {
    static int cnt = 0;
    return 0;
    /*static int cnt = 0;
    if(yydebug)
        cout << "----------- meetEOF(" << cnt << ")\n";
    switch (++cnt) {
        case 0:
            if(yydebug)
                cout << "-------- return teol\n";
            return teol;
        case 1:
            if(yydebug)
                cout << "-------- return teof\n";
            return teof;
    }
    return 0;*/
}

int goOutdent(char prev) {
    int top = indentLvs.size() ? indentLvs.top() : 0;
    if (nowIndent >= top) return 0;

    indentLvs.pop();
    unput(prev);
    unput('\n');
    changeRule("DEDENT", dedent);

    if (yydebug) {
        cout << " ----- prev=" << prev << " nowIndent=" << nowIndent << "\n";
        cout << " ----- dedent: pop! now " << indentLvs.size() << " dedentLv left. \n";
    }

    return tdedent;
}

int nowRule = INITIAL;
int prevRule = INITIAL;

int yywrap()
{
    return 1;
}
