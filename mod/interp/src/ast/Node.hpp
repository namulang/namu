#pragma once

#include "Clonable.hpp"
#include "../type/WType.hpp"
#include "../container/native/NChain.hpp"
#include "../container/native/NArr.hpp"

namespace wrd {

    class Node : public Instance, public Clonable, public Asable {
        WRD_INTERFACE(Node, Instance)

    public:
        virtual NContainer& subs() = 0;
        const NContainer& subs() const WRD_UNCONST_FUNC(subs())

        NArr sub(const std::string& name) const {
            return subs().get([&](const Node& elem) {
                return elem.getName() == name;
            });
        }
        NArr sub(const std::string& name, const NContainer& args) {
            return sub(name, _createTypesFromArgs(args));
        }
        NArr sub(const std::string& name, const WTypes& types) {
            return subs().get([&](const Node& elem) {
                return elem.getName() == name && elem.canRun(types);
            });
        }
        NArr sub(const std::string& name, const NContainer& args) const WRD_UNCONST_FUNC(sub(name, args))
        NArr sub(const std::string& name, const WTypes& types) const WRD_UNCONST_FUNC(sub(name, types))

        virtual wbool canRun(const WTypes& types) const = 0;
        wbool canRun(const NContainer& args) const {
            return canRun(_createTypesFromArgs(args));
        }

        virtual Str run(NContainer& args) = 0;
        /// release all holding resources and ready to be terminated.
        /// @remark some class won't be able to reinitialize after rel() got called.
        virtual void rel() {}

        virtual const std::string& getName() const {
            static std::string dummy = "";
            return dummy;
        }
        // Asable:
        using Asable::is;
        wbool is(const Type& type) const override {
            return getType().is(type);
        }

        using Asable::as;
        Ref as(const Node& it) const override;

    private:
        static WTypes _createTypesFromArgs(const NContainer& args) {
            WTypes ret;
            for(Iter e=args.head(); e ;e++)
                ret.push_back(const_cast<WType*>(&e->getType()));
            return ret;
        }
    };

    /// managed object.
    /*class NObj : public Obj {
        WRD_CLASS(NObj, Obj)

    public:
        NObj(): Super("", new NArr()) {}
    };*/

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

    class Func : public Scope {
        WRD_CLASS(Func, Scope)

    public:
        Ret<Ref> run(Arr& args) override;
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
