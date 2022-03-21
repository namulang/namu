// nested class of tnmap.hpp:
//  this file allows to be refered by 'tnmap.hpp' file only.
class nmapIteration : public iteration {
    WRD(CLASS(nmapIteration, iteration))
    friend class tnmap;

public:
    nmapIteration(tnmap& own, citer citer): _own(own), _citer(citer) {}

    wbool isEnd() const override {
        return _citer == _own.end();
    }

    /// if iteration reached to the last element to iterate, it can precede to next,
    /// which means to the End of a buffer.
    /// however, this step wasn't regarded to a step even though it proceeds.
    wcnt next(wcnt step) override {
        std::advance(_citer, step);
        return step;
    }
    using super::getKey;
    K& getKey() override {
        if(isEnd()) return nulOf<K>();
        return _citer->first;
    }
    using super::getVal;
    V& getVal() override {
        if(isEnd()) return nulOf<V>();
        return *_citer->second;
    }
    using super::getContainer;
    tnbicontainer<K, V>& getContainer() override { return _own; }

protected:
    wbool _onSame(const typeProvidable& rhs) const override {
        const me& cast = (const me&) rhs;
        return isFrom(cast.getContainer()) && _citer == rhs._citer;
    }

private:
    tnmap& _own;
    citer _citer; // cpp map's iterator.
};
