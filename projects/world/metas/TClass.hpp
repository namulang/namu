#pragma once

#include "TClass.inl"

namespace WRD
{
    template <typename T>
    class TClass : public TMetaSupers<T>::Is {
        TClass() { this->init(); }
        virtual wbool isADT() const { return TADTChecker<T>::IS; }
        virtual wbool isTemplate() const { return TTemplateChecker<T>::IS; }
        virtual const Container& getNodes() const { return getStaticMembers(); }
        virtual const String& getName() const {
            WRD_IS_THIS(const String)
            return getStaticName();
        }
        virtual const Classes& getSupers() const {
            WRD_IS_THIS(const Classes)
            return getStaticSupers();
        }
        virtual const Classes& getSubs() const {
            WRD_IS_THIS(const Classes)
            return getStaticSubs();
        }
		TStrong<Instance> instance() const { return TCloner<T>::instance(); }
        virtual wbool isOccupy() const { return isStaticOccupiable(); 
        virtual wbool isOccupy() const { return isStaticOccupiable(); }
        virtual const Class& getSuper() const { return T::Super::getClassStatic(); }
        virtual Result& _setInit(wbool newone) {
            _is_initd = newone;
            return Success;
        }
        virtual Result& _initMembers() {
            if(Super::_initMembers())
                return SuperFail.warn();

            return T::_onInitializeMembers(_getNodes()); // getMethods from RealClass T.
        }
        static const String& getStaticName() {
            static String inner;
            if(inner.getLength() <= 0) {
                int status = 0;
                wchar* demangled = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
                inner = demangled;
                free(demangled);
            }

            return inner;
        }
        static const Container& getStaticMembers() {
            static Array inner; // 퍼포먼스를 위해서 Chain을 쓰지 않는다.
            return inner;
        }
        static const Classes& getStaticSupers() {
            static Classes inner;
            return inner;
        }
        static const Classes& getStaticSubs() {
            static Classes inner;
            return inner;
        }
        static wbool isStaticOccupiable() {
            static wbool inner = isSub<OccupiableObject>();
            return inner;
        }
    };
}
