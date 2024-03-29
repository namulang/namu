#include "forExpr.hpp"
#include "../../builtin.hpp"
#include "../../visitor/visitor.hpp"
#include "../../frame/thread.hpp"
#include "../../frame/frameInteract.hpp"

namespace namu {

    NAMU(DEF_ME(forExpr), DEF_VISIT())

    me::forExpr(const std::string& localName, const node& container, const blockExpr& blk):
        super(blk), _container(container), _name(localName), _initEval(false) {}

    const std::string& me::getLocalName() const {
        return _name;
    }

    str me::getContainer() {
        return *_container;
    }

    str me::run(const args& a) {
        blockExpr& blk = getBlock();
        if(nul(blk) || !_container)
            return NAMU_E("blk or container is null"), str();

        str ased = _container->as<node>();
        if(!ased) return NAMU_E("ased is null"), str();
        str iter = ased->run("iterate", args{narr{*new nInt(0)}});
        if(!iter) return NAMU_E("iter is null"), str();

        arr& eval = getEval().cast<arr>();
        if(nul(eval))
            return NAMU_E("eval isn't arr"), str();
        arr& ret = *new arr(eval.getType().getBeans()[0]);
        frame& fr = thread::get()._getNowFrame();

        while(!iter->run("isEnd")->cast<nbool>()) {
            str elem = iter->run("get");
            if(!elem)
                return NAMU_E("elem is null"), str();
            frameInteract f1(blk); {
                fr.pushLocal(_name, *elem);

                ret.add(*blk.run());
                if(_postprocess(fr))
                    return ret;
            }

            iter->run("next", args{narr{*new nInt(1)}});
        }

        return ret;
    }

    str me::getEval() const {
        if(_initEval) return super::getEval();

        _initEval = true;
        str ased = _container->getEval();
        str elemType = ased->run("getElemType");
        if(!elemType) return NAMU_E("elemType == null"), str();

        blockExpr& blk = getBlock();
        frameInteract f1(blk); {
            thread::get()._getNowFrame().pushLocal(getLocalName(), (node*) elemType->clone());

            arr& newEval = *new arr(*blk.getEval()); // elem of last stmt.
            setEval(newEval);
            return newEval;
        }
    }
}
