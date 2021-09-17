#pragma once

#include "clonable.hpp"
#include "../builtin/container/native/tnarr.hpp"
#include "validable.hpp"

namespace wrd {

	class ases;

    /// node provides common API to manipulate its sub nodes.
    class node : public instance, public clonable, public validable {
        WRD(INTERFACE(node, instance))

    public:
        node& operator[](const std::string& name) const { return sub(name); }

    public:
        wbool isSub(const type& it) const { return getType().isSub(it); }
        wbool isSuper(const type& it) const { return getType().isSuper(it); }
        template <typename T>
        wbool isSub() const { return getType().isSub<T>(); }
        template <typename T>
        wbool isSuper() const { return getType().isSuper<T>(); }

        virtual ncontainer& subs() = 0;
        const ncontainer& subs() const WRD_UNCONST_FUNC(subs())

        template <typename T>
        node& sub(std::function<wbool(const T&)> l) const {
            return subs().get<T>(l);
        }
        node& sub(const std::string& name) const;
        node& sub(const std::string& name, const ncontainer& args);
        node& sub(const std::string& name, const wtypes& types);
        node& sub(const std::string& name, const ncontainer& args) const;
        node& sub(const std::string& name, const wtypes& types) const;

        template <typename T>
        tnarr<T> subAll(std::function<wbool(const T&)> l) const {
            return subs().getAll<T>(l);
        }
        narr subAll(const std::string& name) const;
        narr subAll(const std::string& name, const ncontainer& args);
        narr subAll(const std::string& name, const wtypes& types);
        narr subAll(const std::string& name, const ncontainer& args) const;
        narr subAll(const std::string& name, const wtypes& types) const;

        virtual wbool canRun(const wtypes& typs) const = 0;
        wbool canRun(const ncontainer& args) const {
            return canRun(_createTypesFromArgs(args));
        }

        virtual str run(const ncontainer& args) = 0;
        str run();

        /// release all holding resources and ready to be terminated.
        /// @remark some class won't be able to reinitialize after rel() got called.
        virtual void rel() {}

        virtual const std::string& getName() const {
            static std::string dummy = "";
            return dummy;
        }

        template <typename T>
        wbool is() const {
            return is(ttype<T>::get());
        }
        wbool is(const type& to) const {
			return getType().is(to);
        }
        template <typename T>
        tstr<T> as() const {
            return as(ttype<T>::get());
        }
        str as(const type& to) const {
			return getType().as(*this, to);
		}

        template <typename T>
        wbool isImpli() const {
            return isImpli(ttype<T>::get());
        }
        wbool isImpli(const type& to) const {
			return getType().isImpli(to);
        }
        template <typename T>
        tstr<T> asImpli() const {
			return asImpli(ttype<T>::get());
		}
        str asImpli(const type& to) const {
			return getType().asImpli(*this, to);
		}

        wbool isValid() const override {
            return true;
        }

    private:
        static wtypes _createTypesFromArgs(const ncontainer& args) {
            wtypes ret;
            for(iter e=args.begin(); e ;e++)
                ret.push_back((wtype*) &e->getType());
            return ret;
        }
    };

    /// managed object.
    /*class NObj : public obj {
        WRD(CLASS(NObj, obj))

    public:
        NObj(): super("", new narr()) {}
    };*/

    /*
    // iteration #1:
    // 강제로 func를 상속한 c++ 클래스를 만들고 그 안에서 hello world 찍기
    // * node의 기본적인 API의 틀만 적기
    // * 아무런 구현이 없는 wtype클래스의 injection
    // * func.run()의 가구현
    // * ref 구현
    class node : public instance, public containable {
        WRD(CLASS(node, instance))

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

        using containable::get;
        template <typename T>
        tarr<T> get(std::string name, wtype... args);
        arr get(std::string name, wtype... args);
        template <typename T>
        tarr<T&> get(std::string name, wtype args[]);
        arr get(std::string name, wtype args[]);
        template <typename T>
        tarr<T> get(std::string);
        arr get(std::string);

        /// @param args nullable.
        virtual ret<ref> run(arr& args);
        ret<ref> run() { return run(nulOf<arr>()); }

        node& getOrigin();

    protected:
        wbool del(node& it) override;
        wbool add(node& it) override;

    private:
        wbool _isInit;
    };

    class ref : public node, tbindable<node> {
        WRD(CLASS(tref, node))

        node& _get() override { return *_ptr; }
        // override get() funcs...
        // isInit...

        wbool isBind() { return _ptr.isBind(); }
        // override tbindable...

        ret<ref> run(arr& args) override;

        str _ptr;
    };

    template <typename T>
    class tref : public ref {
    };

    class func : public scope {
        WRD(CLASS(func, scope))

    public:
        ret<ref> run(arr& args) override;
    };




    // iteration #2:
    // 강제로 AST를 조직함. Console 이라는 obj 안에 있는 void print(msg str)를 실행하는 callExpr 실행
    // 강제로 obj를 scope에 등록을 해둔 상태에서 callexpr를 실행함.
    // * obj
    // * str
    // * wtype의 묵시적 형변환
    // * 묵시적 형변환을 수행하는 func.run()
    // * scope의 obj scope 등록 기능
    // * obj의 scope 등록
   class obj : public scope {
   };
    class str : public obj {
    };
    class Chain {
    };
    class frame : ? {
    };
    class stackFrame : public ?? {
    };
    class Expr : public node {
    };
    class CallExpr : public Expr {
    };
   class wtype : public type {
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
    // Visitation과 bison을 활용해서 func 호출과 정의 할 수있게 만듬
    // * bison, lex
    // * Visitor, visitation
    // * funcDefExpr
    class Visitable {
    };
    class Visitation : public instance, public Visitable {
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
    // * 코드를 수행하는 thread
    class ImportExpr : public Expr {
    };
    class thread : public ? {
    }; */
}
