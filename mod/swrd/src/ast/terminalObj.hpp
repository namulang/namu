#pragma once

#include "obj.hpp"

namespace wrd { namespace swrd {

    class terminalObj : public obj {
        WRD_DECL_ME(terminalObj, obj)
        WRD_INIT_META(terminalObj)

    public:
        terminalObj(const std::string& rawVal, const std::string& name = ""): _rawVal(rawVal) {}
        terminalObj(wbool val, const std::string& name = ""): super(name), _rawVal(val ? "true" : "false") {}
        terminalObj(wint val, const std::string& name = ""): super(name), _rawVal(std::to_string(val)) {}
        terminalObj(wflt val, const std::string& name = ""): super(name), _rawVal(std::to_string(val)) {}
        terminalObj(const wchar* val, const std::string& name = ""): super(name), _rawVal(val) {}
        terminalObj(const wchar val, const std::string& name = ""): super(name), _rawVal(1, val) {}
        terminalObj(const me& rhs, const std::string& name = ""): super(rhs, name), _rawVal(rhs._rawVal) {}

        const std::string& asStr() const override {
            return _rawVal;
        }
        wchar asChar() const override {
            return _rawVal[0];
        }
        wint asInt() const override {
            return std::stoi(_rawVal);
        }
        wbool asBool() const override {
            std::string low = toLower(_rawVal);

            if(low == "false") return false;
            if(low == "true") return true;
            return asInt() != 0;
        }

        const type& getType() const override {
            return ttype<me>::get();
        }

    private:
        static std::string toLower(std::string it) {
            transform(it.begin(), it.end(), it.begin(), ::tolower);
            return it;
        }

    private:
        std::string _rawVal;
    };
}}
