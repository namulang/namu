#pragma once

#include "../../../ast.hpp"
#include "../../../bridge/cpp/tcppBridge.hpp"

namespace namu {

    // another f**king annoying MSVC Hack:
    //  to avoid C2901 error, I need to declare sort of dllexport(import) things at here.
    //  spended plenty of hours again to find out the reason. thank you so much.
    typedef class _nout tcppBridge<narr> __argSuperClass;

    class _nout arr : public __argSuperClass, public tucontainable<node>, tarrayable<node> {
        NAMU(CLASS(arr, __argSuperClass), VISIT())
        typedef typename tucontainable<node>::iter iter;
        typedef typename tucontainable<node>::iteration iteration;
        typedef std::map<const type*, tstr<scope>> cache;
        static inline const std::string TYPENAME = "T";

    public:
        arr();
        arr(const node& newType);

    public:
        using tarrayable<node>::operator[];
        node& operator[](nidx n) override;

    public:
        const node& getElemType() const {
            return *_type;
        }

        using super::subs;
        nbicontainer& subs() override {
            static cache c;
            str as = _type->as<node>();
            const type* key = &as->getType();
            auto e = c.find(key);
            if(e != c.end())
                return e->second.get();

            // this is first try to generalize type T:
            return _defGeneric(c, key);
        }

        ncnt len() const override;

        nbool has(nidx n) const override;

        //  get:
        using tarrayable<node>::get;
        using tucontainable<node>::get;
        using super::get;
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

    protected:
        iteration* _onMakeIteration(ncnt step) const override;

    private:
        scope& _defGeneric(cache& c, const type* key);
        scope& _getOriginScope();

    private:
        str _type;
    };
}
