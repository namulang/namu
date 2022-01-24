#pragma once

#include "../builtin/container/native/tnchain.inl"

namespace wrd {

    class scopeStack : public instance, clonable {
        WRD(CLASS(scopeStack, instance))

    public:
        tstr<nchain>& getTop() { return _top; }
        tstr<nchain>& getBottom() { return _bottom; }

        wcnt len() const {
            return _top ? _top->len() : 0;
        }
        wcnt chainLen() const {
            return _top ? _top->chainLen() : 0;
        }

        wbool push(nchain& scope) {
            // bind scope first:
            //  variable 'scope' can be a 'new'ed variable by push(ncontainer&) func.
            //  the 'chain' class uses binder when it iterates element.
            //  so if you call chainLen(), then our fresh 'scope' variable will be binded
            //  to binder of a iterater.
            //  so when iterator dies, the 'scope' variable also got freed.
            //  to prevent this case, you have to care about the variable if it has been
            //  passed from the heap. or you will encounter the annoying BAD_ACCESS crash.
            //
            //      so REMEMBER. bind it first or put it into a container first.
            tstr<nchain> lifeSpanner(scope);
            wcnt len = scope.chainLen();
            if(len == 0) return true;
            if(len != 1)
                return WRD_E("can't bind scopes into local stack if it's more than 2."), false;

            if(_top)
                scope.link(*_top);
            else
                _bottom.bind(scope);

            WRD_DI("localStack.push(Chain(%x))", this, &scope);
            return _top.bind(scope);
        }

        tstr<nchain> pop() {
            if(!_top) return tstr<nchain>();

            tstr<nchain> ret(_top);
            _top.bind(_top->getNext());
            if(!_top)
                _bottom.rel();
            WRD_DI("localStack.pop(%x), .next=%x", &ret.get(), &_top.get());
            return ret;
        }

        void rel() {
            _top.rel();
            _bottom.rel();
        }

    private:
        tstr<nchain> _top;
        tstr<nchain> _bottom;
    };
}
