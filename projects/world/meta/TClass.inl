#pragma once

#include "helpers.hpp"
#include "ObjectClass.hpp"

namespace wrd 
{
    class Str;
    class Res;
    class Container;
    class Classes;

    template <typename T>
    class TClass : public TMetaSuper<T>::Is
    {	WRD_CLASS_DECL(TClass<T>, typename TMetaSuper<T>::Is)
    public:
        TClass();

    public:
		// Class:
        virtual wbool isADT() const;
        virtual wbool isTemplate() const;
        virtual const Str& getName() const;
        virtual const Classes& getSupers() const;
        virtual const Classes& getSubs() const;
        virtual TStrong<Instance> instance() const;
		virtual wcnt getSize() const;
		//	Node:
        virtual const Container& getNodes() const;
		//	State:
        virtual wbool isOccupy() const;
		virtual wbool isInit() const;
		virtual Res& init();
		//	Thing:
		virtual const Class& getSuper() const;

	protected:
		//	Composit:
		virtual Res& _initNodes();

    public:
        static const Str& getNameStatic();
        static const Container& getNodesStatic();
        static const Classes& getSupersStatic();
        static const Classes& getSubsStatic();
		static const Class& getSuperStatic();
        static wbool isOccupyStatic();
		static wbool isADTStatic();
		static wbool isTemplateStatic();
		static wbool isInitStatic();

	private:
		static wbool __is_init;
    };
}
