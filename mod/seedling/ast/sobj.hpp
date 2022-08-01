#pragma once

#include "../common.hpp"

namespace wrd {

    class _wout sobj : public instance {
        WRD_DECL_ME(sobj, instance)
        WRD_INIT_META(sobj)

        typedef std::map<std::string, tstr<me>> myMap;
        typedef myMap::iterator iterator;

    public:
        sobj(std::initializer_list<me*> subs, const std::string& name = "");
        sobj(const me& rhs, const std::string& name = "");
        sobj(const std::string& name = "");

    public:
        me& operator[](const std::string& name);
        const me& operator[](const std::string& name) const WRD_UNCONST_FUNC(operator[](name))
        me& operator[](widx n);
        const me& operator[](widx n) const WRD_UNCONST_FUNC(operator[](n))

        explicit operator wbool() const;

        me& sub(const std::string& name);
        const me& sub(const std::string& name) const WRD_UNCONST_FUNC(sub(name))

        wbool has(const std::string& name) const;

        void add(const sobj& new1);
        void add(std::initializer_list<sobj*> subs);
        void del(const sobj& it);
        void del(const std::string& name);

        const std::string& getName() const;
        void setName(const std::string& newName);

        wcnt len() const;

        iterator begin();
        iterator end();

        const type& getType() const override;

        virtual wint asInt() const;
        virtual wchar asChar() const;
        virtual const std::string& asStr() const;
        virtual wbool asBool() const;
        virtual wbool isExist() const;

    private:
        myMap _subs;
        std::string _name;
    };
}
