#include "../common/dep.hpp"
#include <functional>

using namespace wrd;
using namespace std;

namespace {
    class myfunc : public mgdFunc {
        WRD_CLASS(myfunc, mgdFunc)

    public:
        myfunc(std::string name = "myfunc"): super(name) {
            WRD_E("myfunc(%x) new", this);
        }
        ~myfunc() {
            WRD_E("myfunc(%x) delete", this);
        }

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
        str _onRun(narr& args) override {
            WRD_I("hello world!");
            _executed = true;

            if(_lambda)
                _res = _lambda(args, (stackFrame&) wrd::thread::get().getStackFrame());
            return str();
        }

    private:
        wbool _executed;
        wbool _res;
        function<wbool(const ncontainer&, const stackFrame&)> _lambda;
        wtypes _types;
    };
}

wbool checkFrameHasfuncAndObjScope(const frame& fr, const func& func, const obj& obj) {
    if(nul(fr)) return false;

    int n = 0;
    WRD_E("fr.len=%d", fr.subs().len());
    for(wrd::iterator e=fr.subs().begin(); e ;e++)
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
    if(foundfunc.len() != 1)
        return WRD_E("couldn't find %s func on frame(%x)", func.getName().c_str(), &fr), false;

    return true;
}

namespace {
    struct myObj : public mgdObj {
        WRD_CLASS(myObj, mgdObj)

    public:
        using super::getCtors;
        funcs& getCtors() override {
            static funcs inner;
            return inner;
        }
    };
}

TEST(funcTest, testfuncConstructNewFrame) {
    myObj obj;
    myfunc func;
    func.getTypes().push_back(&obj.getType());
    obj.subs().add(func);
    WRD_E("obj.len=%d", obj.subs().len());
    int n = 0;
    for(wrd::iterator e=obj.subs().begin(); e ;e++) {
        WRD_E(" - fr[%d]=%s", n++, e->getType().getName().c_str());
    }

    narr args;
    args.add(obj);

    func.setLambda([&func, &obj](const auto& args, const auto& sf) {
        if(sf.len() != 1) return false;

        return checkFrameHasfuncAndObjScope(sf[0], func, obj);
    });

    ASSERT_EQ(wrd::thread::get().getStackFrame().len(), 0);
    func.run(args);
    ASSERT_EQ(wrd::thread::get().getStackFrame().len(), 0);
    ASSERT_TRUE(func.isRun());
    ASSERT_TRUE(func.isSuccess());
    ASSERT_TRUE(func.isSuccess());
    func.setLambda(nullptr);
}

TEST(funcTest, testCallfuncInsidefunc) {
    myObj obj1;
    myfunc obj1func1("obj1func1");
    obj1func1.getTypes().push_back(&obj1.getType());
    myfunc obj1func2("obj1func2");
    obj1func2.getTypes().push_back(&obj1.getType());
    obj1.subs().add(obj1func1);
    obj1.subs().add(obj1func2);

    myObj obj2;
    myfunc obj2func1("obj2func1");
    obj2func1.getTypes().push_back(&obj2.getType());
    obj2.subs().add(obj2func1);

    obj1func1.setLambda([&obj1, &obj1func1, &obj1func2](const auto& args, const auto& sf) {
        if(sf.len() != 1) return WRD_E("obj1func1: sf.len() != 1"), false;
        if(!checkFrameHasfuncAndObjScope(sf[0], obj1func1, obj1)) return false;

        narr funcArgs;
        funcArgs.add(obj1);
        obj1func2.run(funcArgs);
        if(sf.len() != 1)
            return WRD_E("return of obj1func1: sf.len() != 1"), false;
        return true;
    });
    obj1func2.setLambda([&obj2, &obj1func2, &obj1, &obj2func1](const auto& args, const auto& sf) {
        if(sf.len() != 2) return WRD_E("obj1func2: sf.len() != 2"), false;

        if(!checkFrameHasfuncAndObjScope(sf[1], obj1func2, obj1)) return false;

        narr funcArgs;
        funcArgs.add(obj2);

        obj2func1.run(funcArgs);
        if(sf.len() != 2)
            return WRD_E("return of obj1func2: sf.len() != 2"), false;
        return true;
    });
    obj2func1.setLambda([&obj2, &obj2func1](const auto& args, const auto& sf) {
        if(sf.len() != 3) return false;

        if(!checkFrameHasfuncAndObjScope(sf[2], obj2func1, obj2)) return false;
        return true;
    });

    narr args;
    args.add(obj1);
    ASSERT_EQ(wrd::thread::get().getStackFrame().len(), 0);
    obj1func1.run(args);
    ASSERT_EQ(wrd::thread::get().getStackFrame().len(), 0);
    ASSERT_TRUE(obj1func1.isSuccess());
}

TEST(funcTest, testfuncHasStrParameter) {
    // prepare:
    std::string expectVal = "hello world!";
    myfunc func1;
    myObj obj;
    obj.subs().add(func1);

    wtypes& types = func1.getTypes();
    types.push_back(&obj.getType());
    types.push_back(&ttype<wStr>::get());
    func1.setLambda([&](const ncontainer& args, const stackFrame& sf) {
        const wtypes& types = func1.getTypes();
        if(args.len() != types.size()) return false;

        const wtype& expectType = *types[1];
        tref<wStr> cast(args.iter(1)->asImpli(expectType));
        if(!cast) return false;

        return cast->get() == expectVal;
    });

    narr args;
    args.add(obj);
    args.add(new wStr(expectVal));
    wrd::iterator e = args.iter(1);

    func1.run(args);
    ASSERT_TRUE(func1.isSuccess());
}
