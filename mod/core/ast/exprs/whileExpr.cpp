#include "whileExpr.hpp"

#include "../../frame/frameInteract.hpp"
#include "../../frame/thread.hpp"
#include "../../worker/visitor/visitor.hpp"

namespace nm {

    NM(DEF_ME(whileExpr), DEF_VISIT())

    me::whileExpr(const node& condition, const blockExpr& blk): super(blk), _condition(condition) {}

    node& me::getCondition() { return *_condition; }

    namespace {
        class whileLoop: public me::loop {
            NM(CLASS(whileLoop, loop))

        public:
            whileLoop(arr& ret, const whileExpr& owner): super(ret), _owner(owner) {}

        public:
            nbool isLooping() override {
                str ased = _owner.getCondition().asImpli<nBool>()
                               orRet NM_E("cast to bool has been failed."),
                    false;
                return ased->cast<nbool>();
            }

        private:
            const whileExpr& _owner;
        };
    }

    tstr<me::loop> me::_makeLoop(arr& ret) const {
        NM_DI("whileExpr: loop");
        return new whileLoop(ret, *this);
    }
} // namespace nm
