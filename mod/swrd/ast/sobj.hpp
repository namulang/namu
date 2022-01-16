#pragma once

#include "../common.hpp"

namespace wrd {

    class sobj : public instance {
        WRD_DECL_ME(sobj, instance)
        WRD_INIT_META(sobj)

        typedef std::map<std::string, tstr<me>> myMap;
        typedef myMap::iterator iterator;

    public:
        sobj(std::initializer_list<me*> subs, const std::string& name = ""): _name(name) {
            add(subs);
        }
        sobj(const me& rhs, const std::string& name = ""): _subs(rhs._subs), _name(name) {}
        sobj(const std::string& name = ""): _name(name) {}

        me& operator[](const std::string& name) {
            return sub(name);
        }
        const me& operator[](const std::string& name) const WRD_UNCONST_FUNC(operator[](name))
        me& operator[](widx n) {
            return *std::next(begin(), n)->second;
        }
        const me& operator[](widx n) const WRD_UNCONST_FUNC(operator[](n))

        explicit operator wbool() const {
            return isExist();
        }

        me& sub(const std::string& name);
        const me& sub(const std::string& name) const WRD_UNCONST_FUNC(sub(name))

        wbool has(const std::string& name) const {
            return _subs.find(name) != _subs.end();
        }

        void add(const sobj& new1) {
            if(nul(new1)) return;

            _subs.insert(make_pair(new1.getName(), tstr<me>(new1)));
        }
        void add(std::initializer_list<sobj*> subs) {
            for(auto e : subs)
                add(*e);
        }
        void del(const sobj& it) {
            del(it.getName());
        }
        void del(const std::string& name) {
            _subs.erase(name);
        }

        const std::string& getName() const {
            return _name;
        }

        void setName(const std::string& newName) {
            _name = newName;
        }

        wcnt len() const {
            return _subs.size();
        }

        iterator begin() {
            return _subs.begin();
        }

        iterator end() {
            return _subs.end();
        }

        const type& getType() const override {
            return ttype<me>::get();
        }

        virtual wint asInt() const { return 0; }
        virtual wchar asChar() const { return '\0'; }
        virtual const std::string& asStr() const {
            static std::string inner;
            return inner;
        }
        virtual wbool asBool() const { return false; }
        virtual wbool isExist() const {
            return true;
        }

    private:
        myMap _subs;
        std::string _name;
    };
}
