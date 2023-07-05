#pragma once

#include "ntype.hpp"
#include "../ast/obj.hpp"

namespace namu {

    class node;
    template <typename T, typename TACTIC> class tnarr;
    typedef tnarr<node, strTactic> narr;

    class _nout mgdType : public ttype<obj> {
        NAMU_DECL_ME(mgdType, ttype<obj>)

    public:
        mgdType(const std::string& name): _name(name) { _initSupers(ttype<obj>::get()); }
        mgdType(const std::string& name, const mgdType& super): _name(name) { _initSupers(super); }
        mgdType(const std::string& name, const narr& bean);
        mgdType(const std::string& name, const mgdType& super, const narr& bean);

    public:
        const type& getSuper() const override { return *_supers[_supers.size()-1]; }
        const nbool& isInit() const override {
            static nbool inner = true;
            return inner;
        }
        const std::string& getName() const override { return _name; }

        // TODO: getSubs(), getLeafs()

    protected:
        types& _getSupers() override {
            return _supers;
        }

    private:
        void _initSupers(const type& super) {
            const types& supers = super.getSupers();
            _supers.insert(_supers.end(), supers.begin(), supers.end());
            _supers.push_back((type*) &super);
        }

    private:
        std::string _name;
        types _supers;
    };
}
