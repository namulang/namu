#include "../common/dep.hpp"
#include <functional>

using namespace wrd;
using namespace std;

namespace {
    class myfunc : public func {
        WRD_CLASS(myfunc, func)

    public:
        myfunc(std::string name = "myfunc"): super(name) {
            WRD_E("myfunc(%x) new", this);
        }
        ~myfunc() {
            WRD_E("myfunc(%x) delete", this);
        }

        using super::subs;
        ncontainer& subs() override { return _shares; }

        void setUp() {
            _executed = false;
            _res = false;
        }

        wbool isRun() const {
            return _executed;
        }

        void setLambda(function<wbool(const ncontainer&, const stackFrame&)> lambda) {
            _lambda = lambda;
        }

        wbool isSuccess() const {
            return _res;
        }

        const wtypes& getTypes() const override { return _types; }
        wtypes& getTypes() { return _types; }

        const wtype& getReturnType() const override {
            return ttype<node>::get();
        }

    protected:
        str _onRun(ncontainer& args) override {
            WRD_I("hello world!");
            _executed = true;

            if(_lambda)
                _res = _lambda(args, (stackFrame&) thread::get().getStackFrame());
            return str();
        }

    private:
        wbool _executed;
        wbool _res;
        function<wbool(const ncontainer&, const stackFrame&)> _lambda;
        narr _shares;
        wtypes _types;
    };
}

wbool checkFrameHasfuncAndObjScope(const frame& fr, const func& func, const obj& obj) {
    if(nul(fr)) return false;

    int n = 0;
    WRD_E("fr.len=%d", fr.subs().getLen());
    for(wrd::iterator e=fr.subs().head(); e ;e++)
        WRD_E(" - func(\"%s\") calls: fr[%d]=%s", func.getName().c_str(), n++, e->getType().getName().c_str());

    const nchain& funcScope = fr.subs().cast<nchain>();
    if(nul(funcScope)) return WRD_E("nul(funcScope)"), false;
    if(&func.subs() != &funcScope.getContainer())
        return WRD_E("func.subs(%x) != funcScope(%x)", &func.subs(), &funcScope), false;

    const nchain& objScope = funcScope.getNext();
    if(nul(objScope)) return WRD_E("nul(objScope)"), false;
    if(&obj.subs() != &objScope)
        return WRD_E("obj.subs(%x) != objScope(%x)", &obj.subs(), &objScope), false;

    narr foundfunc = fr.sub(func.getName());
    if(foundfunc.getLen() != 1)
        return WRD_E("couldn't find %s func on frame(%x)", func.getName().c_str(), &fr), false;

    return true;
}

TEST(funcFixture, testfuncConstructNewFrame) {
    obj obj;
    myfunc func;
    obj.subs().add(func);
    WRD_E("obj.len=%d", obj.subs().getLen());
    int n = 0;
    for(wrd::iterator e=obj.subs().head(); e ;e++) {
        WRD_E(" - fr[%d]=%s", n++, e->getType().getName().c_str());
    }

    narr args;
    args.add(obj);

    func.setLambda([&func, &obj](const auto& args, const auto& sf) {
        if(sf.getLen() != 1) return false;

        return checkFrameHasfuncAndObjScope(sf[0], func, obj);
    });

    func.run(args);
    ASSERT_TRUE(func.isRun());
    ASSERT_TRUE(func.isSuccess());
    ASSERT_TRUE(func.isSuccess());
    func.setLambda(nullptr);
}

TEST(funcFixture, testCallfuncInsidefunc) {
    obj obj1;
    myfunc obj1func1("obj1func1");
    myfunc obj1func2("obj1func2");
    obj1.subs().add(obj1func1);
    obj1.subs().add(obj1func2);

    obj obj2;
    myfunc obj2func1("obj2func1");
    obj2.subs().add(obj2func1);

    obj1func1.setLambda([&obj1, &obj1func1, &obj1func2](const auto& args, const auto& sf) {
        if(sf.getLen() != 1) return WRD_E("obj1func1: sf.getLen() != 1"), false;
        if(!checkFrameHasfuncAndObjScope(sf[0], obj1func1, obj1)) return false;

        narr funcArgs;
        funcArgs.add(obj1);
        obj1func2.run(funcArgs);
        if(sf.getLen() != 1)
            return WRD_E("return of obj1func1: sf.getLen() != 1"), false;
        return true;
    });
    obj1func2.setLambda([&obj2, &obj1func2, &obj1, &obj2func1](const auto& args, const auto& sf) {
        if(sf.getLen() != 2) return WRD_E("obj1func2: sf.getLen() != 2"), false;

        if(!checkFrameHasfuncAndObjScope(sf[1], obj1func2, obj1)) return false;

        narr funcArgs;
        funcArgs.add(obj2);

        obj2func1.run(funcArgs);
        if(sf.getLen() != 2)
            return WRD_E("return of obj1func2: sf.getLen() != 2"), false;
        return true;
    });
    obj2func1.setLambda([&obj2, &obj2func1](const auto& args, const auto& sf) {
        if(sf.getLen() != 3) return false;

        if(!checkFrameHasfuncAndObjScope(sf[2], obj2func1, obj2)) return false;
        return true;
    });

    narr args;
    args.add(obj1);
    obj1func1.run(args);
    ASSERT_TRUE(obj1func1.isSuccess());
}

TEST(funcFixture, testfuncHasStrParameter) {
    // prepare:
    std::string expectVal = "hello world!";
    myfunc func1;
    obj obj;
    obj.subs().add(func1);

    wtypes& types = func1.getTypes();
    types.push_back(&obj.getType());
    types.push_back(&ttype<strObj>::get());
    func1.setLambda([&](const ncontainer& args, const stackFrame& sf) {
        const wtypes& types = func1.getTypes();
        if(args.getLen() != types.size()) return false;

        const wtype& expectType = *types[1];
        tref<strObj> cast(args.iter(1)->asImpli(expectType));
        if(!cast) return false;

        return cast->get() == expectVal;
    });

    narr args;
    args.add(obj);
    args.add(new strObj(expectVal));
    wrd::iterator e = args.iter(1);
    node& elem1 = *e;
    strObj& cast = elem1.cast<strObj>();

    func1.run(args);
    ASSERT_TRUE(func1.isSuccess());
}
