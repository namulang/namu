#pragma once

#include "helpers.hpp"
#include "TConcreteClass.inl"
#include "TInterfaceClass.inl"
#include "ObjectClass.hpp"

namespace wrd 
{
    class Str;
    class Result;
    class Container;
    class Classes;

    template <typename T>
    class TClass : public TMetaSuper<T>::Is
    {
    public:
        TClass();

    public:    // Class:
        virtual wbool isADT() const;
        virtual wbool isTemplate() const;
        virtual const Str& getName() const;
        virtual const Classes& getSupers() const;
        virtual const Classes& getSubs() const;

    public: // Node:
        virtual const Container& getMembers() const;
        virtual wbool isInit() const;
        virtual wbool isOccupiable() const;
        virtual Result& _setInit(wbool newone);
        virtual Result& _initNodes();

    public:
        static const Str& getStaticName();
        static const Container& getStaticNodes();
        static const Classes& getStaticSupers();
        static const Classes& getStaticSubs();
        static wbool isStaticOccupiable();

    private:
        static wbool _is_init;
    };
}
