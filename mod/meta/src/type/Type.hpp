#pragma once

#include "../common.hpp"

namespace wrd {
    /// @remark Type returning TType<Type> as result of getType()
    ///         because this func always returns metaclass no matter of what This type is,
    ///         users need to care about getting meta of metaclass on calling getType().
    ///         for example,
    ///             Thing& thing1 = ...; // let's assume that got from outside.
    ///             Object obj;
    ///
    ///             wbool compare = obj.isSub(thing1.getType()); // user intend to get class of Thing.
    ///             // however, value 'compare' will definitely be false if
    ///             // thing was actually a retrived one by calling Thing.getType() before.
    ///
    ///             // because Type::getType() will return TType<TType<T> >,
    ///             // that stmt will be translated that checks object vs TType<T>.
    class Type {
        WRD_DECL_THIS(Type)

    public:
        virtual wbool operator==(This& rhs);
        wbool operator==(This&& rhs) { return operator==(rhs); }
        wbool operator!=(This& rhs);
        wbool operator!=(This&& rhs) { return operator!=(rhs); }

        virtual wbool isTemplate() = 0;
        virtual wbool isAbstract() = 0;
        virtual const std::string& getName() = 0;

        /// @brief  create an instance to be refered this type.
        /// @remark available when the type defines a ctor without any params.
        /// @return return an address of new instance, however, if ctor without any params
        ///         isn't defined, then returns null.
        virtual void* make() = 0;
        template <typename T>
        T* makeAs() {
            return (T*) make();
        }

        virtual wcnt getSize() = 0;
        virtual wbool init();
        virtual wbool rel();
        virtual Type& getSuper() = 0;
        virtual const wbool& isInit() = 0;
        Types& getLeafs();
        virtual Types& getSubs() = 0;
        virtual Types& getSupers() = 0;

        wbool isSuper(Type& it);
        template <typename T> wbool isSuper() { return isSuper(T::get()); }
        wbool isSub(Type& it) { return it.isSuper(*this); }
        template <typename T> wbool isSub() { return T::get().isSuper(*this); }

    protected:
        //  Type:
        virtual Type& _getStatic() = 0;
        void _setInit(wbool newState) {
            const wbool& res = isInit();
            wbool& isInit = const_cast<wbool&>(res);

            isInit = newState;
        }

    private:
        wbool _logInitOk(wbool res);
    };
}
