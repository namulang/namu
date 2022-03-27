#pragma once

#include "param.hpp"
#include "../builtin/container/native/tnarr.hpp"

namespace wrd {

    class signature : public tnarr<param> {
        WRD(CLASS(signature, tnarr<param>)

    public:
        signature(): _id(nullptr) {}
        signature(const std::string& name): _name(name), _id(nullptr) {}
        signature(const std::string& name, std::initializer_list<const param*> elems)
            : super(elems), _name(name), _id(nullptr) {}
        template <typename... Es>
        signature(const std::string& name, const Es&... elems)
            : super(elems...), _name(name), _id(nullptr) {}
        ~signature() override { _rel(); }

    public:
        const std::string& getName() const { return _name; }
        const std::string& get() const {
            if(nul(_id))
                _id = _makeId();
            return _id;
        }
        void rel() override {
            super::rel();
            _rel();
        }

    private:
        void _rel() {
            if(_id)
                delete _id;
        }

        std::string* _makeId() const {
            std::stringstream ss;
            ss << _name;

            if(len()) {
                ss << "(";
                wbool isFirst = true;
                for(auto& p : this) {
                    if(!isFirst) ss << ",";
                    ss << type->getType().getName();
                }
                ss << ")";
            }

            return new std::string(ss.str());
        }

    private:
        mutable std::string* _id;
        std::string _name;
    };
}
