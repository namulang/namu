#pragma once

#include "ntype.hpp"
#include "../ast/obj.hpp"

namespace namu {

    class _nout mgdType : public ttype<obj> {
        NAMU_DECL_ME(mgdType, ttype<obj>)

    public:
        mgdType(const std::string& name): _name(name), _super(&ttype<obj>::get()) { _initSupers(ttype<obj>::get()); }
        mgdType(const std::string& name, const mgdType& super): _name(name) { _initSupers(super); }

    public:
        const type& getSuper() const override { return *_supers[_supers.size()-1]; }
        const nbool& isInit() const override { return true; }
        const std::string& getName() const override { return _name; }
        nbool isCustom() const override { return true; }
        // TODO: getSubs(), getLeafs()

    private:
        void _initSupers(const type& super) {
            const types& supers = super.getSupers();
            _supers.insert(_supers.end(), supers.begin(), supers.end());
            _supers.push_back(super);
        }

    private:
        std::string _name;
        types _supers;
    };
}
