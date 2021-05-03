#pragma once

#include "../../ast/obj.hpp"

namespace wrd {

    class primitiveType : public wtype {
        WRD_DECL_ME(primitiveType, wtype)

    public:
        wbool isImmutable() const override {
            return true;
        }

    protected:
        const casts& _getImplis() const override {
            static casts* inner = nullptr;
            if(inner) return *inner;

            inner = new casts();
            _onCreateImplis(*inner);

            return *inner;
        }
        virtual void _onCreateImplis(casts& tray) const = 0;
    };

    template <typename T>
    class primitiveObj : public obj {
        WRD_INTERFACE(primitiveObj, obj)

    public:
        primitiveObj(): _val() {}
        primitiveObj(const T& val): _val(val) {}

        T& get() { return _val; }
        const T& get() const { return _val; }

    protected:
        wbool _onSame(const typeProvidable& rhs) const override {
            const me& cast = (const me&) rhs;
            return _val == cast._val;
        }

        tnarr<func> _getCtors() const {
            static tstr<tnarr<func>> ctors;
            if(!ctors) {
                tnarr<func>* tray = new tnarr<func>();
                _onCreateCtors(*tray);

                ctors.bind(tray);
            }
        }

        virtual void _onCreateCtors(tnarr<func>& tray) const = 0;

    private:
        T _val;
    };
}
