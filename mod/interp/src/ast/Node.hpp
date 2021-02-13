#pragma once

#include "../common.hpp"

namespace wrd {
    // iteration #1:
    // 강제로 Func를 상속한 c++ 클래스를 만들고 그 안에서 hello world 찍기
    // * node의 기본적인 API의 틀만 적기
    // * 아무런 구현이 없는 WType클래스의 injection
    // * Func.run()의 가구현
    // * ref 구현

    typedef TStr<Node> Str;
    typedef TWeak<Node> Weak;

    class WType : public Type {
        WRD_DECL_THIS(WType, Type)
    };

    class Err {
    };

    template <typename T>
    struct TRet {
        TRet(T newVal, Err& newErr) : v(newVal), e(newErr) {}

        T v;
        TStr<Err> e;
    };

    class Iteratable : public TypeProvidable {
    public:
        virtual wbool isEnd() = 0;
        virtual wbool next() = 0;
        virtual wbool prev() = 0;
        virtual Node& get() = 0;

        virtual wbool hasSame(Containable& it) = 0;
        wbool hasSame(Iter& it) {
            return hasSame(it._step._own.get());
        }
        wbool hasSame(Iteration& it) {
            return hasSame(it._own.get());
        }
    };

    class Iteration : public Iteratable {
        WRD_CLASS(Iteration)
        friend class Iter;

    public:
        Iteration(Containable& own): _own(own) {}

        virtual wbool hasSame(Containable& rhs) {
            return &_own.get() == &rhs;
        }

    protected:
        TWeak<Containable> _own;
    };

    class Iter : public Iteration {
        WRD_CLASS(Iter)
        friend class Iteration;

    public:
        Iter(Iteration* newStep): _step(newStep) {}

        /// @return true if there are more data to proceed
        wbool operator==(This& rhs) { return hasSame(rhs._step); }
        wbool operator==(This&& rhs) { return operator==(rhs); }
        wbool operator++() { return next(); }
        wbool operator--() { return prev(); }
        virtual Node& operator*() { return _get(); }
        virtual Node* operator->() { return &_get(); }
        operator wbool() { return !isEnd(); }

        wbool hasSame(Containable& it) override { return _step->hasSame(it); }
        wbool isEnd() override { return _step->isEnd(rhs); }
        wbool next() override { return _step->next(rhs); }
        wbool prev() override { return _step->prev(rhs); }
        Node& get() override { return _step->get(); }

    private:
        This& _assign(This& rhs) {
            _step.bind(_step->clone());
            return *this;
        }

    protected:
        TStr<Iteration> _step;
    };

    template <typename T>
    class TIter : public Iter {
        WRD_CLASS(TIter, Iter)

    public:
        /// @return true if there are more data to proceed
        T& operator*() override { return (T&) _get(); }
        T* operator->() override { return (T*) &_get(); }

        T& get() override { return (T&) _get(); }
    };

    class Containable {
        WRD_CLASS(Containable)

    public:
        virtual Node& operator[](widx n) { return get(n); }

        virtual wcnt getLen() = 0;

        virtual Node& get(widx n) = 0;
        template <typename T>
        T& get(std::function<wbool(T&)> l); // TODO: use getHead()
        virtual Node& get(std::function<wbool(Node&)> l) { return get<Node>(l); }

        // TODO: set funcs.

        virtual Iter head() { return iter(0); }
        virtual Iter tail() { return iter(getLen() - 1); }
        virtual Iter iter(idx n) = 0;
        virtual Iter iter(Node& elem) {
            Iter ret;
            each([&ret](Iter& e, Node& myelem) {
                if(&elem != &myelem) return true;

                ret = e;
                return false;
            });
            return ret;
        }

        template <typename T>
        void each(Iter& from, Iter& to, std::function<wbool(Iter&, T&)> l) {
            for (Iter e=from; e == to ;++e) {
                T& t = e->cast<T>();
                if(nul(t)) continue;

                if(!l(e, t)) return;
            }
        }
        template <typename T>
        void each(std::function<wbool(Iter&, T&)> l) {
            each(head(), tail(), l);
        }
    };

    class ArrContainable : public Containable {
        WRD_CLASS(ArrContainable, Containable)

    public:
        wbool add(Node& new1) ( return add(tail(), new1); }
        wbool add(Node&& new1) ( return add(new1); }
        wcnt add(Iter&& from, Iter&& to) {
            return add(from, to);
        }
        /// @return how many element has been added from rhs.
        wcnt add(Iter& from, Iter& to) {
            int ret = 0;
            each(from, to, [&ret](Iter& e, Node& elem) {
                if(add(e)) ret++;
            });
            return ret;
        }
        wcnt add(Containable&& rhs) {
            return add(rhs);
        }
        wcnt add(Containable& rhs) {
            return add(rhs.head(), tail());
        }
        virtual wbool add(Iter& e, Node& new1) {
            if(nul(e) || nul(new1)) return false;
            if(!e.hasSame(*this)) return false;
            if(e.isEnd()) return false;

            return true;
        }

        wbool del(Node& it) { return del(iter(it)); }
        /// delete last element if exists.
        wbool del() { return del(tail()); }
        wcnt del(Iter&& from, Iter&& to) {
            return del(from, to);
        }
        wcnt del(Iter& from, Iter& to) {
            int ret = 0;
            each(from, to, [&ret](Iter& e, Node& elem) {
                if(del(e)) ret++;
            });
            return ret;
        }
        wcnt del(Containable& rhs) {
            return del(rhs.head(), rhs.tail());
        }
        /// @return true if element got deleted successfully.
        virtual wbool del(Iter& it) {
            if(nul(it)) return false;
            if(!it.hasSame(*this)) return false;
            if(it.isEnd()) return false;

            return true;
        }
    };

    class MapContainable : public Containable {
        virtual wbool add(Node& key, Node& val) = 0;
        /// @return how many element has been added from rhs.
        wcnt add(Iter& from, Iter& to) {
            int ret = 0;
            each<Pair>(from, to, [&ret](Iter& e, Pair& elem) {
                if(add(elem)) ret++;
            });
            return ret;
        }
        wcnt add(Containable& rhs) {
            return add(rhs.head(), tail());
        }
        wbool add(Node& key, Node& val) {
            return add(Pair(key, val));
        }
        wbool add(Pair&& new1) {
            return add(new1);
        }
        virtual wbool add(Pair& new1) {
            if(nul(new1)) return false;

            return true;
        }

        wbool del(Node& it) { return del(iter(it)); }
        /// delete last element if exists.
        wbool del() { return del(tail()); }
        wcnt del(Iter& from, Iter& to) {
            int ret = 0;
            each(from, to, [&ret](Iter& e, Node& elem) {
                if(del(e)) ret++;
            });
            return ret;
        }
        wcnt del(Containable& rhs) {
            return del(rhs.head(), rhs.tail());
        }
        /// @return true if element got deleted successfully.
        virtual wbool del(Iter& it) {
            if(nul(it)) return false;
            if(!it.hasSame(*this)) return false;
            if(it.isEnd()) return false;

            return true;
        }
    };

    /// @remark prefix 'N' means "native".
    class NArr : public Containable {
        WRD_CLASS(NArr, Containable)

        friend class NArrIteration : public Iteration {
            WRD_CLASS(NArrIteration, Iteration)
            friend class NArr;

        public:
            NArrIteration(NArr& own, widx startN): Super(own), _n(startN) {}

            wbool hasSame(Iteration& rhs) override {
                return Super::hasSame(rhs) && _n == rhs._n;
            }
            wbool isEnd() override {
                return _isValidN(_n);
            }
            wbool next() override {
                if(!_isValidN(_n + 1)) return false;

                _n++;
                return true;
            }
            wbool prev() override {
                if(!_isValidN(_n - 1)) return false;

                _n--;
                return true;
            }
            Node& get() override {
                if(isEnd()) return nulOf<Node>();
                return _arr->get(_n);
            }

        private:
            wbool _isValidN(wdx n) {
                if(!_arr) return true;
                return _arr->_isValidN(n);
            }

            widx _n;
        };

    public:
        wcnt getLen() override {
            return _vec.size();
        };

        Node& get(widx n) override {
            if(!_isValidN(n)) return nulOf<Node>();

            return *_vec[n];
        }
        Iter iter(idx n) override {
            return Iter(new NArrIteration(*this, n));
        }
        wbool add(Iter& e, Node& new1) override {
            if(!Super::add(e, new1)) return false;
            NArrIteration& cast = (NArrIteration&) new1._step;

            widx n = cast._n;
            return _vec.insert(_vec.begin() + n, new1);
        }
        wbool del(Iter& it) override {
            if(!Super::del(it)) return false;
            NArrIteration& cast = (NArrIteration&) new1._step;

            return _vec.erase(_vec.begin() + cast._n);
        }

    private:
        wbool _isValidN(widx n) {
            return n < 0 || n >= getLen();
        }

        std::vector<Str> _vec;
    };

    class Pair : public Obj {
        WRD_CLASS(Pair, Obj)

    public:
        virtual Node& getKey();
        virtual Node& getVal();
    };

    template <typename K, typename V>
    class TPair : public Pair {
        WRD_CLASS(TPair, Pair)

    public:
        K& getKey() override;
        V& getVal() override;
    };

    class NMap : public Containable {
        WRD_CLASS(NMap, Containable)

        friend class NMapIteration : public Iteration {
            WRD_CLASS(NMapIteration, Iteration)
            friend class NMap;

        public:
            NMapIteration(NMap& own,
        };

    private:
        map<Str, Str> _map;
    };

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

/*
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
