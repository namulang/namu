#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>

using namespace std;

class Node {
    public:
        enum Color {
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
        return tab(lv) + _onPrint(lv);
    }
    virtual string _onPrint(int lv) { return ""; }

    static string clr(Color c) {
        return string("\033[") + to_string(c) + "m";
    }

    string tab(int cnt) {
        cout << name() << " -> tab(" << cnt << ")\n";
        static string unit;
        if (unit.size() <= 0) {
            for (int n=0; n < 4/*TAB_WIDTH*/ ;n++)
                unit += " ";
        }

        string ret;
        for (int n=0; n < cnt ;n++)
            ret += unit;
        return ret;
    }

    map<string, Node*> nodes;
};

class Value : public Node {
public:
    Value(string value) : _value(value) {}
    virtual string _onPrint(int lv) {
        return clr(NUMBER) + _value;
    }

    string _value;
};

class Id : public Value {
public:
    Id(string name) : Value(name) {}
    virtual string name() { return "id"; }
    virtual string _onPrint(int lv) {
        return clr(BLUE) + _value;
    }
};

class Origin : public Value {
public:
    Origin(string name) : Value(name) {}
    virtual string name() { return "origin"; }
    virtual string _onPrint(int lv) {
        return clr(TYPE) + _value;
    }
};

class Keyword : public Value {
public:
    Keyword(string name) : Value(name) {}
    virtual string name() { return "keyword"; }
    virtual string _onPrint(int lv) {
        return clr(KEYWORD) + _value;
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
    Bool(bool value) : Value(to_string(value)) {}
    virtual string name() { return "bool"; }
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
    virtual string _onPrint(int lv) {
        return clr(STRING) + _value;
    }
};

class Op2 : public Node {
public:
    Op2(const char* symbol, Node* l, Node* r) : Node(l, r), _symbol(symbol) {}
    virtual string name() { return _symbol; }
    virtual string _onPrint(int lv) {
        return clr(OP) + "(" + l()->print() + " " + clr(OP) + _symbol + " " + r()->print() + clr(OP) + ")";
    }

    const char* _symbol;
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

class SomeAssign : public Node {
public:
    SomeAssign(string symbols, Node* l, Node* r) : Node(l, r), _symbols(symbols) {}

    virtual string name() { return "someassign"; }
    virtual string _onPrint(int lv) {
        return l()->print() + clr(OP) + " " + _symbols + " " + r()->print();
    }

    string _symbols;
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
    virtual string _onPrint(int lv) {
        return clr(OP) + "(" + l()->print() + clr(OP) + ") " + r()->print();
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
            sum += get(n)->print(lv+1);
        return sum;
    }

    int _len;
};

class Block : public Container {
public:
    virtual string name() { return "block"; }
};


class Haver : public Node {
public:
    Haver(Node* con) {
        add("has", con);
    }

    virtual string _onPrint(int lv) {
        return has()->print(lv);
    }

    Node* has() {
        return (Node*) get("has");
    }
};

class BlockHaver : public Haver {
public:
    BlockHaver(Node* what) : Haver(what) {}


    virtual string _onPrint(int lv) {
        return block()->print(lv);
    }

    Block* block() {
        return (Block*) get("block");
        return (Block*) has();
    }
};

class For : public BlockHaver {
public:
    For(Node* id, Node* container, Node* block) : BlockHaver(block) {
        lIs(id);
        rIs(container);
    }

    virtual string name() { return "for"; }
    virtual string _onPrint(int lv) {
        return clr(KEYWORD) + " for" + l()->print() + clr(KEYWORD) + " in " + r()->print() + "\n"+ block()->print(lv);
    }
};



class Branch : public BlockHaver {
public:
    Branch(Node* expr, Node* then): BlockHaver(then) {
        lIs(expr);
    }

    virtual string name() { return "if"; }
    using Node::print;
    virtual string print(int lv) {
        return l()->print() + "\n" + block()->print(lv);
    }
};

class BranchHaver : public Haver {
public:
    BranchHaver(Node* branch): Haver(branch) {}

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
    If(Node* then, vector<Branch*>* elifs, Block* els): BranchHaver(then), _elifs(elifs), _els(els) {}
    If(Node* then) : BranchHaver(then), _els(0) {}
    If(Node* then, Block* els) : BranchHaver(then), _els(els) {}

    virtual string name() { return "if"; }
    virtual string _onPrint(int lv) {
        string elifs;
        if (_elifs)
            for (Branch* e : *_elifs)
                elifs += clr(KEYWORD) + "elif " + e->print(lv);
        string elses = _els ? clr(KEYWORD) + "else \n" + _els->print(lv) : "";
        return clr(KEYWORD) + "if " + BranchHaver::_onPrint(lv) + elifs + elses;
    }

    vector<Branch*>* _elifs;
    Block* _els;
};

class Args : public Container {
public:
    Args() {}
    virtual string name() { return "args"; }
    using Node::print;
    virtual string print(int lv) {
        string sum = len() > 0 ? get(0)->print() : "";
        for (int n=1; n < len() ;n++)
            sum += clr(OP) + ", " + get(n)->print();
        return sum;
    }
};

class TypeList : public Node {
public:
    TypeList() {}
    TypeList(Args* args) : Node(args) {}

    virtual string name() { return "typelist"; }
    virtual string _onPrint(int lv) {
        string ret = clr(CONTAINER) + "(";
        if (l())
            ret += l()->print();
        return ret + clr(CONTAINER) + ")";
    }
};

class Sequence : public Node {
public:
    Sequence(Node* start, Node* end): Node(start, end) {}
    virtual string name() { return "sequence"; }
    virtual string _onPrint(int lv) {
        return l()->print() + clr(CONTAINER) + ".." + r()->print();
    }
};

class Array : public Node {
public:
    Array() {}
    Array(Node* args): Node(args) {}

    virtual string name() { return "array"; }
    virtual string _onPrint(int lv) {
        string ret = clr(CONTAINER) + "[";
        if (l())
            ret += l()->print();
        return ret + clr(CONTAINER) + "]";
    }
};

class Func : public Node {
public:
    Func(string name, TypeList* types) : Node(new Str(name), types) {}

    virtual string name() { return "func"; }
    virtual string _onPrint(int lv) {
        Value* name = (Value*) l();
        return clr(FUNC) + name->_value + r()->print();
    }
};

class Stmt : public Node {
public:
    Stmt() {}
    Stmt(Node* expr) : Node(expr) {}

    virtual string name() { return "stmt"; }
    using Node::print;
    virtual string print(int lv) {
        char newLine = hasHaver() ? '\0' : '\n';
        return l()->print(lv) + clr(WHITE) + newLine;
    }

    bool hasHaver() {
        return dynamic_cast<Haver*>(l());
    }
};

class File : public Node {
public:
    File(Block* blk) : Node(blk) {}
    virtual string name() { return "file"; }
    virtual string _onPrint(int lv) {
        return l()->print(lv-1);
    }
};
