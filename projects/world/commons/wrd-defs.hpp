#pragma once

#include "wrd-deps.hpp"

//	World는 객체 안에서 다른 객체에 접근하는 접근자함수들에 경우에는 DelayingNullCorruption으로 인해 객체가 Null이라고 해도 Null을 반환할뿐 프로그램이 죽지는 않는다.
//	접근자 아닌 경우에는 "속도문제" 로 인해 수행하지 않는다.
//	또한 반환형이 객체에 대한 레퍼런스나 포인터가 아닌경우에도 정상적인 반환값과 겹칠 수있기 때문에 체크하지 않는다.
//	multiple NULL check macro:
//		if you need to check plenty arguments to be checked null
//		and return value will be same, you can accomplish it conveniently
//		with this macro.
//
//		usage:
//			WRD_IS_NULL(arg1, -1)
//			WRD_IS_NULL(arg2, -1)
//			WRD_IS_NULL(arg3, -1)
//				or
//			WRD_ARE_NULL(-1, arg1, arg2, arg3)
#define WRD_IS_NULL_3(VALUE, RES, RET)	\
	if((VALUE).isNull()) {				\
		RES.warn(#VALUE);				\
		return RET;						\
	}
#define WRD_IS_NULL_2(VALUE, RET)	WRD_IS_NULL_3(VALUE, RET, RET)
#define WRD_IS_NULL_1(VALUE)		WRD_IS_NULL_2(VALUE, wasnull)
#define WRD_IS_NULL(...) 			WRD_OVERLOAD(WRD_IS_NULL, __VA_ARGS__)

#define _ARE_NULL(VALUE, RET)		WRD_IS_NULL(VALUE, RET)
#define WRD_ARE_NULL(RET, ...)		NE_EACH_EXPAND(_ARE_NULL, RET, __VA_ARGS__)

#define WRD_IS_THIS_1(TYPE)			WRD_IS_NULL_3(*this, wasnull, nulr<TYPE>())
#define WRD_IS_THIS_0()				WRD_IS_THIS_1(This)
#define WRD_IS_THIS(...) 			WRD_OVERLOAD(WRD_IS_THIS, __VA_ARGS__)

#define WRD_IS_SUPER_1(call)        if(Super:: call ) return superfail;
#define WRD_IS_SUPER_2(res, call)	\
    Res& res = Super:: call ;    	\
    if(res) return superfail;
#define WRD_IS_SUPER(...)			WRD_OVERLOAD(WRD_IS_SUPER, __VA_ARGS__)

#define WRD_IS_CONST(RET)		\
	if((this->isConst())) {		\
		wascancel.warn(#RET);	\
		return RET;				\
	}

#define WRD_ASSERT_4(expr, ret, dump, msg)  \
    if( (expr) )                            \
        return ret.dump(msg);
#define WRD_ASSERT_3(expr, ret, msg)		WRD_ASSERT_4(expr, ret, warn, msg)
#define WRD_ASSERT_2(expr, ret)				WRD_ASSERT_4(expr, ret, warn, "")
#define WRD_ASSERT_1(expr)                  WRD_ASSERT_4(expr, waswrongop, warn, "")
#define WRD_ASSERT(...)                    	WRD_OVERLOAD(WRD_ASSERT, __VA_ARGS__)

#define WRD_IS_RES_5(expr, ret, chk, dump, msg) \
    {                                          	\
        const Res& res = expr;              	\
        WRD_ASSERT(res.chk, ret, dump, msg)    	\
   }
#define WRD_IS_RES_4(expr, chk, dump, msg)  WRD_IS_RES_5(expr, res, chk, dump, msg)
#define WRD_IS_RES_3(expr, chk, msg)        WRD_IS_RES_5(expr, res, chk, warn, msg)
#define WRD_IS_RES_2(expr, chk)            	WRD_IS_RES_5(expr, res, chk, warn, #expr)
#define WRD_IS_RES(...)                    	WRD_OVERLOAD(WRD_IS_RES, __VA_ARGS__)

#define WRD_IS_WARN_3(expr, ret, msg)      	WRD_IS_RES(expr, ret, isWarn(), warn, msg)
#define WRD_IS_WARN_2(expr, ret)            WRD_IS_RES(expr, ret, isWarn(), warn, #expr)
#define WRD_IS_WARN_1(expr)                	WRD_IS_RES(expr, isWarn())
#define WRD_IS_WARN(...)                    WRD_OVERLOAD(WRD_IS_WARN, __VA_ARGS__)

#define WRD_IS_ERR_3(expr, ret, msg)        WRD_IS_RES(expr, ret, isErr(), err, msg)
#define WRD_IS_ERR_2(expr, ret)            	WRD_IS_RES(expr, ret, isErr(), err, #expr)
#define WRD_IS_ERR_1(expr)                  WRD_IS_RES(expr, isErr())
#define WRD_IS_ERR(...)                    	WRD_OVERLOAD(WRD_IS_ERR, __VA_ARGS__)
#define WRD_IS_GOOD_3(expr, ret, msg)      	WRD_IS_RES(expr, ret, isGood(), info, msg)
#define WRD_IS_GOOD_2(expr, ret)            WRD_IS_RES(expr, ret, isGood(), info, #expr)	
#define WRD_IS_GOOD_1(expr)              	WRD_IS_RES(expr, isGood())
#define WRD_IS_GOOD(...)                    WRD_OVERLOAD(WRD_IS_GOOD, __VA_ARGS__)

#define _CLASS_BASE()													\
    public:																\
        virtual WRD_LAZY_METHOD_4(Class&, getClass, const, TClass<This>)\
        TStrong<This> clone() const { return TStrong<This>(_clone()); }	\
	protected:															\
		virtual TStrong<Instance> _clone() const { 						\
			return TCloner<This>::clone(*this);							\
		}																\
	private:
#define WRD_CLASS_2(THIS, SUPER)\
    WRD_INHERIT_2(THIS, SUPER) 	\
    _CLASS_BASE()
#define WRD_CLASS_1(THIS)		\
    WRD_INHERIT_1(THIS)			\
    _CLASS_BASE()
#define WRD_CLASS(...) 			WRD_OVERLOAD(WRD_CLASS, __VA_ARGS__)

/// This macros, DECLARE, DEFINE, will be used for which can't dependent to TClass and TStrong and Instance.
///	mostly, base classes for them will be correspond to and will be used for internal usage only.
#define _CLASS_DECL_BASE()						\
	public:										\
		virtual const Class& getClass() const;	\
		TStrong<This> clone() const;			\
	protected:									\
		virtual TStrong<Instance> _clone() const;\
	private:
#define WRD_CLASS_DECL_2(THIS, SUPER)		\
	WRD_INHERIT_2(THIS, SUPER)				\
	_CLASS_DECL_BASE()
#define WRD_CLASS_DECL_1(THIS)	\
	WRD_INHERIT_1(THIS)			\
	_CLASS_DECL_BASE()
#define WRD_CLASS_DECL(...) WRD_OVERLOAD(WRD_CLASS_DECL, __VA_ARGS__)

///    this macro should be placed at implement file which include header file using DECLARE macro.
#define WRD_CLASS_DEF_1(THIS)        			WRD_CLASS_DEF_2(WRD_VOID(), THIS)
#define WRD_CLASS_DEF_2(TEMPL, THIS)				\
    TEMPL const Class& THIS::getClass() const {		\
        static TClass<This> inner;    				\
        return inner;    							\
    }    											\
    TEMPL TStrong<Instance> THIS::_clone() const {	\
        return TCloner<THIS>::clone(*this);    		\
	}
#define WRD_CLASS_DEF(...)            			WRD_OVERLOAD(WRD_CLASS_DEF, __VA_ARGS__)
