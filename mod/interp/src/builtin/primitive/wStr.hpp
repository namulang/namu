#pragma once

#include "primitiveObj.hpp"

namespace wrd {

    class wStr : public primitiveObj<std::string> {

        class strType : public primitiveType {
            WRD_DECL_ME(strType, primitiveType)

        protected:
            void _onCreateImplis(casts& tray) const override {
                struct toWInt: public cast {
                    const wtype& getType() const override {
                        // TODO:
                        return nulOf<wtype>();
                    }
                    ref as(const node& wStr) const override {
                        // TODO:
                        return ref();
                    }
                };
                tray.push_back(new toWInt());
            }
        };

        WRD_CLASS(wStr, primitiveObj, strType)

    public:
        wStr() {}
        wStr(const std::string& val): super(val) {}

    protected:
        void _onCreateCtors(tnarr<func>& tray) const override {
        }
    };
}
