#pragma once

#include "../../../bridge/cpp/tgenericCppBridge.hpp"

namespace namu {

    // another f**king annoying MSVC Hack:
    //  to avoid C2901 error, I need to declare sort of dllexport(import) things at here.
    //  spended plenty of hours again to find out the reason. thank you so much.
    typedef class _nout tgenericCppBridge<narr> __argSuperClass;

    class _nout arr : public __argSuperClass, public tucontainable<node>, tarrayable<node> {
        NAMU(CLASS(arr, __argSuperClass), VISIT())
        typedef typename tucontainable<node>::iter iter;
        typedef typename tucontainable<node>::iteration iteration;
        typedef std::map<const type*, tstr<scope>> cache;
        static inline const std::string TYPENAME = "T";

    public:
        arr();
        arr(const node& elemType);

    public:
        using tarrayable<node>::operator[];
        node& operator[](nidx n) override;

    public:
        using super::subs;
        nbicontainer& subs() override {
            const type* key = &getElemType().getType();
            auto e = _cache.find(key);
            if(e != _cache.end())
                return e->second.get();

            // this is first try to generalize type T:
            return _defGeneric(key);
        }

        ncnt len() const override;

        nbool has(nidx n) const override;

        //  get:
        using tarrayable<node>::get;
        using super::get;
        template <typename E>
        E& get(std::function<nbool(const E&)> l) const {
            for(const node& elem : *this) {
                const E& cast = elem.template cast<E>();
                if(!nul(cast) && l(cast)) // elem should be typeProvidable.
                    return (E&) cast;
            }

            return nulOf<E>();
        }

        node& get(std::function<nbool(const node&)> l) const {
            return this->get<node>(l);
        }

        template <typename E>
        tnarr<E, strTactic> getAll(std::function<nbool(const E&)> l) const {
            tnarr<E> ret;
            for(const node& elem : *this) {
                const E& cast = elem.template cast<E>();
                if(!nul(cast) && l(cast))
                    ret.add(cast);
            }

            return ret;
        }

        narr getAll(std::function<nbool(const node&)> l) const {
            return this->getAll<node>(l);
        }

        node& get(nidx n) override;

        //  set:
        using tucontainable<node>::set;
        using tarrayable<node>::set;
        nbool set(const iter& at, const node& new1) override;
        nbool set(nidx n, const node& new1) override;

        //  add:
        using tucontainable<node>::add;
        using tarrayable<node>::add;
        nbool add(const iter& at, const node& new1) override;
        nbool add(nidx n, const node& new1) override;
        void add(const iter& here, const iter& from, const iter& to) override;

        //  del:
        using tucontainable<node>::del;
        nbool del(nidx n) override;
        nbool del(const iter& it) override;
        nbool del(const iter& from, const iter& to) override;

        //  etc:
        clonable* deepClone() const override;
        void rel() override;

        const obj& getOrigin() const override {
            if(!_org)
                _org.bind(new me(getElemType()));
            return *_org;
        }

    protected:
        iteration* _onMakeIteration(ncnt step) const override;

    private:
        scope& _defGeneric(const type* key);
        scope& _getOriginScope();

    private:
        static inline cache _cache;
    };
}
