#pragma once

#include "../common.hpp"

namespace wrd {


    class Node : public Instance {
        WRD_INTERFACE(Node, Instance)
    };

    /*
    // iteration #1:
    // 강제로 Func를 상속한 c++ 클래스를 만들고 그 안에서 hello world 찍기
    // * node의 기본적인 API의 틀만 적기
    // * 아무런 구현이 없는 WType클래스의 injection
    // * Func.run()의 가구현
    // * ref 구현
    class Node : public Instance, public Containable {
        WRD_CLASS(Node, Instance)

    public:
        wbool isInit() {
            return _isInit;
        }

        virtual wbool init() {
            if(isInit()) return true;

            _setInit(true)
            return true;
        }

        virtual void rel() {
            _setInit(false);
        }

        void _setInit(wbool newVal) { _isInit = newVal; }
        virtual SequentialContainer getSubs() = 0;

        using Containable::get;
        template <typename T>
        TArr<T> get(std::string name, WType... args);
        Arr get(std::string name, WType... args);
        template <typename T>
        TArr<T&> get(std::string name, WType args[]);
        Arr get(std::string name, WType args[]);
        template <typename T>
        TArr<T> get(std::string);
        Arr get(std::string);

        /// @param args nullable.
        virtual Ret<Ref> run(Arr& args);
        Ret<Ref> run() { return run(nulOf<Arr>()); }

        Node& getOrigin();

    protected:
        wbool del(Node& it) override;
        wbool add(Node& it) override;

    private:
        wbool _isInit;
    };

    class Ref : public Node, TBindable<Node> {
        WRD_CLASS(TRef, Node)

        Node& _get() override { return *_ptr; }
        // override get() funcs...
        // isInit...

        wbool isBind() { return _ptr.isBind(); }
        // override TBindable...

        Ret<Ref> run(Arr& args) override;

        Str _ptr;
    };

    template <typename T>
    class TRef : public Ref {
    };

    class Scope : public Node {
        Container getSubs() override {
            return _scope;
        }

        Chain _scope;
    };
    class Func : public Scope {
        WRD_CLASS(Func, Scope)

    public:
        Ret<Ref> run(Arr& args) override;
    };

    class Container : public Obj {
        wcnt getLen() override;

        wcnt _len;
    };

    class SequentialContainer : public Container {
        using Container::add;
        virtual wbool add(Node& it, widx at) = 0;
        using Container::del;
        virtual wbool del(widx at) = 0;
    };

    class Arr : public SequentialContainer {
        WRD_CLASS(Arr, SequentialContainer)

    public:
        Arr();
        Arr(vector<Node*>& rhs);
        Arr(vector<Str>& rhs);
        Arr(wcnt len, Node rhs[]);
        Arr(wcnt len, Node... rhs);
        Arr(This& rhs);

        std::vector<Str> _vector;
    };

    template <typename T>
    class TArr : public Arr {
    };

    class Chain : public SequentialContainer {
    };

    template <typename T>
    class TChain : public Chain {
    };

    // iteration #2:
    // 강제로 AST를 조직함. Console 이라는 obj 안에 있는 void print(msg str)를 실행하는 callExpr 실행
    // 강제로 obj를 scope에 등록을 해둔 상태에서 callexpr를 실행함.
    // * Obj
    // * Str
    // * WType의 묵시적 형변환
    // * 묵시적 형변환을 수행하는 Func.run()
    // * scope의 obj scope 등록 기능
    // * obj의 scope 등록
   class Obj : public Scope {
   };
    class Str : public Obj {
    };
    class Chain {
    };
    class Frame : ? {
    };
    class StackFrame : public ?? {
    };
    class Expr : public Node {
    };
    class CallExpr : public Expr {
    };
   class WType : public Type {
   };

    // iteration #3:
    // BlockExpr 로 앞선 callExpr를 하도록 AST를 작성. 변수의 정의, 접근을 수행하는 expr 추가.
    // sys 라는 module 을 강제로 만들고 그 안에 console obj를 둠. origin obj를 정의함.
    // * module scope 기반으로 한 origin obj의 scope 구성
    class Module : ? {
    };
    class Moduler : ? {
    };
    class BlockExpr : {
    };
    class AccessExpr : ? {
    };
    class DeclExpr : ? {
    };

    // iteration #4:
    // bridge API를 만들어서 외부의 test c++ 클래스를 불러와 moduler에 넣을 수 있도록 함.
    // 매우 단순한 test c++ 모듈 1개 작성
    // * module import.

    // iteration #5:
    // Visitation과 bison을 활용해서 Func 호출과 정의 할 수있게 만듬
    // * bison, lex
    // * Visitor, visitation
    // * FuncDefExpr
    class Visitable {
    };
    class Visitation : public Instance, public Visitable {
    };
    template <typename T, typename S = Visitation>
    class TVisitation : public S {
    };
    class Visitor : public Thing, public Visitable {
    };
    template <typename T>
    class TVisitor : public Visitor {
    };

    // iteration #5:
    // 간단한 메인함수 안에 test 모듈의 print(msg str)를 호출 하게 .wrd파일의 interpreting
    // * importExpr
    // * moduler는 시작시 scanning
    // * 만든걸 모두 연동
    // * 코드를 수행하는 Thread
    class ImportExpr : public Expr {
    };
    class Thread : public ? {
    }; */
}
