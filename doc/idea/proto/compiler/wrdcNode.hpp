#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

extern bool USE_OP;
extern int yydebug;

class Node {
    public:
        enum Color {
            NONE = 0,
            RED = 31,
            GREEN = 32,
            WHITE = 37,
            BLUE = 34,
            YELLOW = 33,
            MAGENTA = 35,
            CYAN = 36,

            OP = RED,
            PLAIN = WHITE,
            CONTAINER = GREEN,
            TYPE = BLUE,
            FUNC = YELLOW,
            KEYWORD = CYAN,
            STRING = MAGENTA,
            NUMBER = MAGENTA,
        };

    Node() {}
    Node(Node* l) { lIs(l); }
    Node(Node* l, Node* r) {
        lIs(l);
        rIs(r);
    }

    void add(const string& key, Node* new1) {
        nodes.insert(make_pair(key, new1));
    }
    Node* get(const string& key) {
        return nodes[key];
    }

    void lIs(Node* new1) {
        add("l", new1);
    }
    virtual string name() = 0;
    void rIs(Node* new1) {
        add("r", new1);
    }
    Node* l() { return get("l"); }
    Node* r() { return get("r"); }
    string print() { return print(0); }
    virtual string print(int lv) {
        return _onPrint(lv);
    }
    static Color over;
    virtual string print(int lv, Color color) {
        over = color;
        string ret = _onPrint(lv);
        over = NONE;
        return ret;
    }
    virtual string _onPrint(int lv) { return ""; }

    static string clr(Color c)
    {
        if(over != NONE && c != over) return clr(over);

        return string("\033[") + to_string(c) + "m";
    }

    string tab(int cnt) {
        static string unit;
        if (unit.size() <= 0) {
            for (int n=0; n < 4/*TAB_WIDTH*/ ;n++)
                unit += " ";
        }

        string ret;
        for (int n=0; n < cnt ;n++)
            ret += unit;
        if (yydebug) cout << "------------ tab: " << name() << "(" << cnt << ")\n";
        return ret;
    }

    map<string, Node*> nodes;
};

class Value : public Node {
public:
    Value(string value) : _value(value) {}
    using Node::print;
    virtual string _onPrint(int lv) {
        return clr(NUMBER) + _value;
    }

    string _value;
};

class Id : public Value {
public:
    Id(string name) : Value(name) {}
    virtual string name() { return "id"; }
    using Node::print;
    virtual string _onPrint(int lv) {
        int color = _getColor(_value);
        return clr(Color(color)) + _value;
    }

    int _getColor(const string& value) {
        static vector<string> prebuilt({
            "null",
            "got",
            "super",
            "this",
            "me",
        });

        for(string e : prebuilt)
            if(_value == e) return RED;

        return TYPE;
    }
};

class Origin : public Node {
public:
    Origin(Node* name) : Node(name) {}
    virtual string name() { return "origin"; }
    using Node::print;
    virtual string _onPrint(int lv) {
        return clr(TYPE) + l()->print(lv);
    }
};

class MapOrigin : public Node {
public:
    MapOrigin(Node* val, Node* key): Node(val, key) {}

    virtual string name() { return "mapOrigin"; }
    virtual string _onPrint(int lv) {
        return l()->print(lv) + clr(TYPE) + "{" + r()->print(lv) + clr(TYPE) + "}";
    }
};


class Int : public Value {
public:
    Int(int value) : Value(to_string(value)) {}
    virtual string name() { return "int"; }
};
class Char : public Value {
public:
    Char(char value) : Value(to_string(value)) {}
    virtual string name() { return "char"; }
};
class Float : public Value {
public:
    Float(float value) : Value(to_string(value)) {}
    virtual string name() { return "float"; }
};
class Bool : public Value {
public:
    Bool(bool value) : Value(value ? "true" : "false") {}
    virtual string name() { return "bool"; }
    using Node::print;
    virtual string _onPrint(int lv) {
        return clr(KEYWORD) + _value;
    }
};
class Void : public Value {
public:
    Void() : Value("") {}
    virtual string name() { return "void"; }
};
class Str : public Value {
public:
    Str(string value) : Value(value) {}
    virtual string name() { return "str"; }
    using Node::print;
    virtual string _onPrint(int lv) {
        return clr(STRING) + _value;
    }
};

class Unary : public Node {
public:
    Unary(Node* l, Node* r): Node(l, r) {}

    virtual string name() { return "upre"; }
    virtual string _onPrint(int lv) {
        return l()->print(lv) + r()->print(lv);
    }
};
class UPre : public Unary {
public:
    UPre(Node* symbol, Node* id): Unary(symbol, id) {}
};
class UPost : public Unary {
public:
    UPost(Node* symbol, Node* id): Unary(id, symbol) {}
};

class Op2 : public Node {
public:
    Op2(const char* symbol, Node* l, Node* r) : Node(l, r), _symbol(symbol) {}
    virtual string name() { return _symbol; }
    using Node::print;
    virtual string _onPrint(int lv) {
        string  lStr = l() ? l()->print(lv) : "",
                rStr = r() ? r()->print(lv) : "";

        string body = lStr + " " + clr(OP) + _symbol + " " + rStr;

        if(USE_OP)
            return clr(OP) + "(" + body + clr(OP) + ")";
        return body;
    }

    const char* _symbol;
};

class Param : public Node {
public:
    Param(Node* type, Node* var): Node(type, var) {}

    virtual string name() { return "param"; }
    virtual string _onPrint(int lv) {
        return l()->print(lv) + " " + r()->print(lv);
    }
};

class Plus : public Op2 {
public:
    Plus(Node* l, Node* r) : Op2("+", l, r) {}
};
class Minus : public Op2 {
public:
    Minus(Node* l, Node* r) : Op2("-", l, r) {}
};
class Square : public Op2 {
public:
    Square(Node* l, Node* r) : Op2("*", l, r) {}
};
class Divide : public Op2 {
public:
    Divide(Node* l, Node* r) : Op2("/", l, r) {}
};
class Moduler : public Op2 {
public:
    Moduler(Node* l, Node* r) : Op2("%", l, r) {}
};
class Power : public Op2 {
public:
    Power(Node* l, Node* r) : Op2("^", l, r) {}
};
class Less : public Op2 {
public:
    Less(Node* l, Node* r) : Op2("<", l, r) {}
};
class LessEqual : public Op2 {
public:
    LessEqual(Node* l, Node* r) : Op2("<=", l, r) {}
};
class More : public Op2 {
public:
    More(Node* l, Node* r) : Op2(">", l, r) {}
};
class MoreEqual : public Op2 {
public:
    MoreEqual(Node* l, Node* r) : Op2(">=", l, r) {}
};
class Equal : public Op2 {
public:
    Equal(Node* l, Node* r) : Op2("==", l, r) {}
};
class NotEqual : public Op2 {
public:
    NotEqual(Node* l, Node* r) : Op2("!=", l, r) {}
};
class RefEqual : public Op2 {
public:
    RefEqual(Node* l, Node* r) : Op2("===", l, r) {}
};
class NotRefEqual : public Op2 {
public:
    NotRefEqual(Node* l, Node* r) : Op2("!==", l, r) {}
};
class And : public Op2 {
public:
    And(Node* l, Node* r): Op2("&", l, r) {}
};
class Or : public Op2 {
public:
    Or(Node* l, Node* r): Op2("|", l, r) {}
};

class Redirect : public Op2 {
public:
    Redirect(Node* l, Node* r): Op2("=>", l, r) {}
    Redirect(Node* l): Op2("=>", l, 0) {}
    Redirect(): Op2("=>", 0, 0) {}

    virtual string _onPrint(int lv) {
        string  lStr = l() ? l()->print(lv) : "",
                rStr = r() ? r()->print(lv) : "";
        return lStr + " " + clr(OP) + _symbol + " " + rStr;
    }
};



class SomeAssign : public Node {
public:
    SomeAssign(string symbols, Node* l, Node* r) : Node(l, r), _symbols(symbols) {}

    virtual string name() { return "someassign"; }
    using Node::print;
    virtual string _onPrint(int lv) {
        return l()->print(lv) + clr(OP) + " " + _symbols + " " + r()->print(lv);
    }

    string _symbols;
};

class Access : public Node {
public:
    Access(Node* obj, Node* member): Node(obj, member) {}

    virtual string name() { return "access"; }
    virtual string _onPrint(int lv) {
        return l()->print(lv) + clr(OP) + "." + r()->print(lv);
    }
};

class ContainerAccess : public Node {
public:
    ContainerAccess(Node* container, Node* key): Node(container, key) {}

    virtual string name() { return "containerAccess"; }
    virtual string _onPrint(int lv) {
        return l()->print(lv) + clr(CONTAINER) + "[" + r()->print(lv) + clr(CONTAINER) + "]";
    }
};


class SafeAccess : public Node {
public:
    SafeAccess(Node* obj, Node* member): Node(obj, member) {}
    virtual string name() { return "safeAccess"; }
    virtual string _onPrint(int lv) {
        return l()->print(lv) + clr(OP) + "?." + r()->print(lv);
    }
};


class Assign : public SomeAssign {
public:
    Assign(Node* l, Node* r) : SomeAssign("=", l, r) {}
};

class DefAssign : public SomeAssign {
public:
    DefAssign(Node* l, Node* r) : SomeAssign(":=", l, r) {}
};

class PlusAssign : public SomeAssign {
public:
    PlusAssign(Node* l, Node* r) : SomeAssign("+=", l, r) {}
};

class MinusAssign : public SomeAssign {
public:
    MinusAssign(Node* l, Node* r) : SomeAssign("-=", l, r) {}
};

class SquareAssign : public SomeAssign {
public:
    SquareAssign(Node* l, Node* r) : SomeAssign("*=", l, r) {}
};

class DivideAssign : public SomeAssign {
public:
    DivideAssign(Node* l, Node* r) : SomeAssign("/=", l, r) {}
};

class ModulerAssign : public SomeAssign {
public:
    ModulerAssign(Node* l, Node* r) : SomeAssign("%=", l, r) {}
};

class PowAssign : public SomeAssign {
public:
    PowAssign(Node* l, Node* r) : SomeAssign("^=", l, r) {}
};

class Cast : public Node {
public:
    Cast(Node* to, Node* from) : Node(to, from) {}
    virtual string name() { return "cast"; }
    using Node::print;
    virtual string _onPrint(int lv) {
        string castType = USE_OP ? clr(OP) + "(" + l()->print(lv) + clr(OP) + ")" : l()->print(lv);

        return castType + " " + r()->print(lv);
    }
};


class Out : public Node {
public:
    Out(Node* id): Node(id) {}
    virtual string name() { return "out"; }
    virtual string _onPrint(int lv) {
        return clr(KEYWORD) + "out " + l()->print(lv);
    }
};


class Container : public Node {
public:

    Container() : _len(0) {}
    using Node::add;
    void add(Node* new1) {
        nodes.insert(make_pair(to_string(_len).c_str(), new1));
        _len++;
    }
    using Node::get;
    Node* get(int n) {
        return nodes[to_string(n)];
    }
    int len() {
        return _len;
    }

    using Node::print;
    virtual string print(int lv) {
        string sum;
        for (int n=0; n < len() ;n++)
            sum += get(n)->print(lv + 1);
        return sum;
    }

    int _len;
};

class Block : public Container {
public:
    virtual string name() { return "block"; }

    virtual string print(int lv) {
        return "\n" + Container::print(lv);
    }
};









class Haver : public Node {
public:
    Haver(Node* con) {
        add("has", con);
    }

    Node* has() {
        return (Block*) get("has");
    }
};

class BlockHaver : public Haver {
public:
    BlockHaver(Node* what) : Haver(what) {}

    virtual string _onPrint(int lv) {
        return block()->print(lv);
    }
    Block* block() {
        return (Block*) has();
    }
};

class Return : public Node {
public:
    Return(string name, Node* what): Node(what), _name(name) {}

    virtual string name() { return "return"; }
    virtual string _onPrint(int lv) {
        return clr(RED) + _name + " " +  l()->print(lv);
    }

    string _name;
};

class Next: public Node {
public:
    virtual string name() { return "next"; }
    virtual string _onPrint(int lv) {
        return clr(RED) + "next";
    }
};

class For : public BlockHaver {
public:
    For(Node* id, Node* container, Container* block) : BlockHaver(block) {
        lIs(id);
        rIs(container);
    }
    For(Node* cond, Container* block): BlockHaver(block) {
        lIs(cond);
    }

    virtual string name() { return "for"; }
    using Node::print;
    virtual string _onPrint(int lv) {
        string  id = l() ? l()->print(lv) : "",
                in = r() ? clr(KEYWORD) + " in " + r()->print(lv) : "";

        return clr(KEYWORD) + "for " + id + in + block()->print(lv);
    }
};

class With : public BlockHaver {
public:
    With(Node* id, Node* block): BlockHaver(block) {
        lIs(id);
    }
    With(Node* block): BlockHaver(block) {}

    virtual string name() { return "with"; }
    virtual string _onPrint(int lv) {
        string id = l() ? l()->print(lv) : "";
        return clr(KEYWORD) + "with " + id + block()->print(lv);
    }
};

class Branch : public BlockHaver {
public:
    Branch(Node* expr, Container* then): BlockHaver(then) {
        lIs(expr);
    }

    virtual string name() { return "if"; }
    using Node::print;
    virtual string print(int lv) {
        return l()->print(lv) + block()->print(lv);
    }
};

class BranchHaver : public Haver {
public:
    BranchHaver(Node* branch) : Haver(branch) {}

    using Node::print;
    virtual string _onPrint(int lv) {
        return branch()->print(lv);
    }

    Branch* branch() {
        return (Branch*) has();
    }
};

class If : public BranchHaver {

public:
    If(Branch* then, vector<Branch*>* elifs, Block* els): BranchHaver(then), _elifs(elifs), _els(els) {}
    If(Branch* then) : BranchHaver(then), _els(0) {}
    If(Branch* then, Block* els) : BranchHaver(then), _els(els) {}

    virtual string name() { return "if"; }
    virtual string _onPrint(int lv) {
        string elifs;
        if (_elifs)
            for (Branch* e : *_elifs)
                elifs += tab(lv) + clr(KEYWORD) + "elif " + e->print(lv);
        string elses = _els ? tab(lv) + clr(KEYWORD) + "else" + _els->print(lv) : "";
        return clr(KEYWORD) + "if " + BranchHaver::_onPrint(lv) + elifs + elses;
    }

    vector<Branch*>* _elifs;
    Block* _els;
};




class Tuple : public Node {
public:
    Tuple(Node* val, Node* key): Node(val, key) {}

    virtual string name() { return "tuple"; }
    virtual string _onPrint(int lv) {
        return l()->print(lv) + clr(CONTAINER) + ":" + r()->print(lv);
    }
};

class Args : public Container {
public:
    Args() {}
    virtual string name() { return "args"; }
    using Node::print;
    virtual string print(int lv) {
        string sum = len() > 0 ? get(0)->print() : "";
        for (int n=1; n < len() ;n++)
            sum += clr(CONTAINER) + ", " + get(n)->print();
        return sum;
    }
};

class List : public Node {
public:
    List() {}
    List(Args* args) : Node(args) {}

    virtual string name() { return "list"; }
    using Node::print;
    void add(Node* args) {
        lIs(args);
    }
    virtual string _onPrint(int lv) {
        string ret = clr(CONTAINER) + "(";
        if (l())
            ret += l()->print();
        return ret + clr(CONTAINER) + ")";
    }
};

class Sequence : public Node {
public:
    Sequence(Node* start, Node* end) : Node(start, end) {}

    virtual string name() { return "sequence"; }
    virtual string _onPrint(int lv) {
        return l()->print() + clr(CONTAINER) + ".." + r()->print();
    }
};

class Array : public Node {
public:
    Array() {}
    Array(Node* args) : Node(args) {}

    virtual string name() { return "array"; }
    virtual string _onPrint(int lv) {
        string ret = clr(CONTAINER) + "{";
        if (l())
            ret += l()->print(lv);
        return ret + clr(CONTAINER) + "}";
    }
};

class Func : public BlockHaver {
public:
    Func(Node* lRedirect, Node* retType, Node* name, Node* params, Node* rRedirect, Node* block): BlockHaver(block) {
        add("lRedirect", lRedirect);
        add("retType", retType);
        add("name", name);
        add("params", params);
        add("rRedirect", rRedirect);
    }

    virtual string name() { return "func"; }
    virtual string _onPrint(int lv) {
        Node* blk = has();
        string  name = get("name") ? get("name")->print(lv, FUNC) : "",
                blkStr = blk ? blk->print(lv) : "",
                params = get("params") ? get("params")->print(lv) : "",
                lRed = get("lRedirect") ? get("lRedirect")->print(lv) : "",
                rRed = get("rRedirect") ? get("rRedirect")->print(lv) : "",
                retType = get("retType") ? get("retType")->print(lv) + " ": "";

        return lRed + retType + name + clr(CONTAINER) + "(" + params + clr(CONTAINER) + ")" +
            rRed + blkStr;
    }

    string _name;
};

class Def : public BlockHaver {
public:
    Def(Node* name, Node* list, Node* from, Node* block): BlockHaver(block) {
        add("name", name);
        add("from", from);
        add("list", list);
    }

    virtual string name() { return "def"; }
    virtual string _onPrint(int lv) {
        Node* from = get("from");
        string  name = clr(TYPE) + (get("name") ? get("name")->print(lv) : ""),
                ls = get("list") ? get("list")->print(lv) : "",
                fromStr = from ? clr(KEYWORD) + " from "+ clr(TYPE) + from->print(lv) : "",
                blk = has() ? has()->print(lv) : "";

        return clr(KEYWORD) + "def " + name + ls + fromStr + blk;
    }

    string _name;
};


class Prop : public BlockHaver {
public:
    Prop(Node* name, Node* list, Node* from, Node* blk): BlockHaver(blk) {
        add("name", name);
        add("list", list);
        add("from", from);
    }

    virtual string name() { return "prop"; }
    virtual string _onPrint(int lv) {
        string  n = get("name") ? get("name")->print(lv) : "",
                f = get("from") ? get("from")->print(lv) : "",
                list = get("list") ? get("list")->print(lv) : "",
                blk = has() ? has()->print(lv) : "";

        return clr(KEYWORD) + "prop" + n + list + " from " + f + blk;
    }
};


class FuncCall : public Node {
public:
    FuncCall(Node* name, Node* types) : Node(name, types) {}

    virtual string name() { return "funcCall"; }
    using Node::print;
    virtual string _onPrint(int lv) {
        return l()->print(lv, FUNC) + r()->print(lv);
    }
};

class Stmt : public Node {
public:
    Stmt() {}
    Stmt(Node* expr) : Node(expr) {}

    virtual string name() { return "stmt"; }
    using Node::print;
    virtual string print(int lv) {
        string newLine = hasHaver(l(), 1) ? "" : "\n";
        return tab(lv) + l()->print(lv) + clr(WHITE) + newLine;
    }

    bool hasHaver(Node* it, int c) {
        if(!it) return false;
        Haver* haver = dynamic_cast<Haver*>(it);
        if(haver && haver->has()) {
            if(yydebug) cout << "------------- hasHaver: " << it->name() << "return true\n";
            return true;
        }

        // search manually all of children.
        map<string, Node*>& map = it->nodes;
        std::map<string, Node*>::iterator e = map.begin();
        int n=0;
        while(e != map.end()) {
            Node* child = e->second;
            if (yydebug) cout << "------------- hasHaver: loops[" << it->name() << "][" << c << "] child[" << n << "]=" << (child ? child->name() : "") << "\n";
            if(hasHaver(child, c+1)) return true;
            e++;
            n++;
        }

        return false;
    }
};

class InlineStmt : public Stmt {
public:
    InlineStmt() {}
    InlineStmt(Node* expr): Stmt(expr) {}

    virtual string name() { return "inlineStmt"; }
    virtual string print(int lv) {
        return clr(OP) + ": " + l()->print(lv) + "\n";
            }
};

class ImportStmt : public Node {
public:
    ImportStmt(Node* access): Node(access) {}
    virtual string name() { return "import"; }
    virtual string print(int lv) {
        return tab(lv) + clr(KEYWORD) + "import " + l()->print(lv) + "\n";
    }
};

class File : public Container {
public:
    virtual string name() { return "file"; }
    using Node::print;
    Node* getHeader() const { return _head; }
    void setHeader(Node* h) {
        _head = h;
    }

    virtual string print(int lv) {
        if (_head)
            _head->print(lv);
        return Container::print(lv);
    }

    Node* _head;
};
