#include "defVarExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../loader/interpreter/tverification.hpp"
#include "../../loader/interpreter/verifier.hpp"

namespace wrd {

    WRD_DEF_ME(defVarExpr)

    str me::run(const ucontainable& args) {
        const std::string& name = _param.getName();
        node& org = (node&) *_param.getOrigin();

        if(_where)
            _where->add(name, org);
        else
            thread::get()._getNowFrame().pushLocal(name, org);

        return str(org);
    }

    WRD_VERIFY(defVarExpr, defineVariable, {
        if(!it.run()) {
            const ref& param = it.getParam();
            _err(28, param.getName().c_str(), param.getOrigin().getType().getName().c_str());
        }
    })
}
