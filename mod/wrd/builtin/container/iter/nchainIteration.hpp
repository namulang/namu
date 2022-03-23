// nested class of tnchain.hpp:
//  this file allows to be refered by 'tnchain.hpp' file only.
class chainIteration : public iteration {
    WRD(CLASS(chainIteration, iteration))
    friend class tnchain;

public:
    chainIteration(const tnchain& iteratingChain, const iter& conIter)
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
            _iter = _ownIter->_map->begin();
            if(_iter) remain--;
        }

        return step - remain;
    }

    using super::getContainer;
    tnbicontainer<K, V>& getContainer() override {
        if(!_ownIter) return nulOf<super>();
        return _ownIter->template cast<tnbicontainer<K, V>>();
    }

    using super::getKey;
    K& getKey() override {
        return _iter.getKey();
    }

    using super::getVal;
    V& getVal() override {
        return _iter.getVal();
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
