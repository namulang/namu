#include "getExpr.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verification.inl"
#include "../../loader/interpreter/verifier.hpp"
#include "../../frame/thread.hpp"
#include "../node.inl"
#include "../visitor.hpp"

namespace namu {

    NAMU(DEF_ME(getExpr), DEF_VISIT())

    const node& me::getMe() const {
        if(!_me)
            return thread::get().getNowFrame();
        return *_me;
    }

    const node& me::getEval() const {
        str got = _get();
        if(!got)
            return nulOf<node>();
        return got->getEval();
    }

    str me::run(const args& a) {
        // believe that this expression was checked to be valid.
        return _get();
    }

    const std::string& me::getSubName() const { return _name; }

    /// @return nullable
    const args& me::getSubArgs() const { return *_args; }

    str me::_get() const {
        NAMU_DI("_name=%s", _name.c_str());
        const node& me = getMe();
        if(nul(me)) return NAMU_E("me == null"), str();
        str evalMe = me.as<node>();
        if(!evalMe) return NAMU_E("from == null"), str();

        std::string argsName = _args ? _args->asStr().c_str() : "{}";
        NAMU_DI("%s.sub(%s, %s)", evalMe->getType().getName().c_str(), _name.c_str(), argsName.c_str());
        if(!_args) return str(evalMe->sub(_name));

        return str(evalMe->sub(_name, *_args));
    }



    NAMU_VERIFY(getExpr, isRunnable, {
        // TODO: I have to check that the evalType has what matched to given _params.
        // Until then, I rather use as() func and it makes slow emmersively.
        NAMU_DI("verify: getExpr: isRunnable: %s.%s", it.getType().getName().c_str(), it.getSubName().c_str());
        if(nul(it.getEval())) return _srcErr(errCode::EVAL_NULL_TYPE);
        str got = it._get();
        if(!got) {
            const node& from = it.getMe();
            return _srcErr(errCode::CANT_ACCESS, from.getType().getName().c_str(), it._name.c_str());
        }

        NAMU_DI("...verified: getExpr: isRunnable: got=%s, it=%s", got->getType().getName().c_str(),
                it.getType().getName().c_str());
    })

    NAMU_VERIFY({
        NAMU_DI("verify: getExpr: visit 'from' subnodes");

        verify((node&) it.getMe());

        NAMU_DI("...verified: getExpr: visit 'from' subnodes");
    })
}
