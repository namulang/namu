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
            COMMENT = GREEN,
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

    virtual string _onPrintIn() { return ""; }
    virtual string _onPrintOut() { return ""; }
    virtual string _onPrint() { return ""; }
    string print() {
        return _onPrintIn() + _onPrint() + _onPrintOut();
    }

    static string clr(Color c)
    {
        return string("\033[") + to_string(c) + "m";
    }

    map<string, Node*> nodes;
};

class Value : public Node {
public:
    Value(string value) : _value(value) {}
    virtual string _onPrint() {
        return clr(NUMBER) + _value;
    }

    string _value;
};

class Id : public Value {
public:
    Id(string name) : Value(name) {}
    virtual string name() { return "id"; }
    virtual string _onPrint() {
        return clr(BLUE) + _value;
    }
};

class Origin : public Value {
public:
    Origin(string name) : Value(name) {}
    virtual string name() { return "origin"; }
    virtual string _onPrint() {
        return clr(TYPE) + _value;
    }
};

class Keyword : public Value {
public:
    Keyword(string name) : Value(name) {}
    virtual string name() { return "keyword"; }
    virtual string _onPrint() {
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
    virtual string _onPrint() {
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
    virtual string _onPrint() {
        return clr(STRING) + _value;
    }
};

class Op2 : public Node {
public:
    Op2(char symbol, Node* l, Node* r) : Node(l, r), _symbol(symbol) {}
    virtual string name() { return to_string(_symbol); }
    virtual string _onPrint() {
        return clr(OP) + "(" + l()->print() + " " + clr(OP) + _symbol + " " + r()->print() + clr(OP) + ")";
    }

    char _symbol;
};

class Plus : public Op2 {
public:
    Plus(Node* l, Node* r) : Op2('+', l, r) {}
};
class Minus : public Op2 {
public:
    Minus(Node* l, Node* r) : Op2('-', l, r) {}
};
class Square : public Op2 {
public:
    Square(Node* l, Node* r) : Op2('*', l, r) {}
};
class Divide : public Op2 {
public:
    Divide(Node* l, Node* r) : Op2('/', l, r) {}
};
class Moduler : public Op2 {
public:
    Moduler(Node* l, Node* r) : Op2('%', l, r) {}
};
class Power : public Op2 {
public:
    Power(Node* l, Node* r) : Op2('^', l, r) {}
};

class SomeAssign : public Node {
public:
    SomeAssign(string symbols, Node* l, Node* r) : Node(l, r), _symbols(symbols) {}

    virtual string name() { return "someassign"; }
    virtual string _onPrint() {
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
    virtual string _onPrint() {
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

    virtual string _onPrint() {
        string sum;
        for (int n=0; n < len() ;n++)
            sum += get(n)->print();
        return sum;
    }

    int _len;
};

class Block : public Container {
public:
    virtual string name() { return "block"; }
};


class BlockHave : public Node {
public:
    BlockHave(Container* con) {
        add("block", con);
    }

    virtual string _onPrint() {
        return block()->print();
    }

    Block* block() {
        return (Block*) get("block");
    }
};

class For : public BlockHave {
public:
    For(Node* id, Node* container, Container* block) : BlockHave(block) {
        lIs(id);
        rIs(container);
    }

    virtual string name() { return "for"; }
    virtual string _onPrint() {
        return clr(KEYWORD) + " " + l()->print() + clr(KEYWORD) + " in " + r()->print() + "\n\t"+ block()->print();
    }
};




class Args : public Container {
public:
    Args() {}
    virtual string name() { return "args"; }
    virtual string _onPrint() {
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
    virtual string _onPrint() {
        string ret = clr(OP) + "(";
        if (l())
            ret += l()->print();
        return ret + clr(OP) + ")";
    }
};

class Func : public Node {
public:
    Func(string name, TypeList* types) : Node(new Str(name), types) {}

    virtual string name() { return "func"; }
    virtual string _onPrint() {
        Value* name = (Value*) l();
        return clr(FUNC) + name->_value + r()->print();
    }
};

class Stmt : public Node {
public:
    Stmt() {}
    Stmt(Node* expr) : Node(expr) {}

    virtual string name() { return "stmt"; }
    virtual string _onPrint() {
        return l()->print() + clr(WHITE) + "\n";
    }
};

class File : public Node {
public:
    File(Block* blk) : Node(blk) {}
    virtual string name() { return "file"; }
    virtual string _onPrint() {
        return l()->print();
    }
};
