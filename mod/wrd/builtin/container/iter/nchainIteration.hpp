// nested class of tnchain.hpp:
//  this file allows to be refered by 'tnchain.hpp' file only.
class elemIteration : public iteration {
    WRD(CLASS(elemIteration, iteration))
    friend class tnchain;

public:
    elemIteration(const tnchain& iteratingChain, const iter& conIter)
        : _ownIter(iteratingChain), _iter(conIter) {
            if(!_iter) next(1);
        }

    wbool isEnd() const override {
        return !_ownIter->_next && !_iter;
    }

    wcnt next(wcnt step) override {
        wcnt remain = step;

        // if _ownIter was invalidated then _iter too.
        while(remain > 0) {
            remain -= _iter.next(remain);
            if(remain <= 0) break;

            // _iter moved to 'End' state now.
            if(isEnd()) break;
            _ownIter = _ownIter->_next;
            _iter = _ownIter->_arr->begin();
            if(_iter) remain--;
        }

        return step - remain;
    }

    using super::getContainer;
    tnucontainer<T>& getContainer() override {
        if(!_ownIter) return nulOf<tnucontainer<T>>();
        return _ownIter->template cast<tnucontainer<T>>();
    }

    using super::get;
    T& get() override {
        return *_iter;
    }

protected:
    wbool _onSame(const typeProvidable& rhs) const override {
        const me& cast = (const me&) rhs;
        return  (isEnd() && cast.isEnd()) ||
                _iter == cast._iter;
    }

private:
    tstr<tnchain> _ownIter; // _ownIter shouldn't be null always.
    iter _iter;
};
