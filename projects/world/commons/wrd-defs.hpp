#pragma once

#include "wrd-deps.hpp"
#include "_TGet.hpp"

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
#define WRD_IS_NULL_2(VALUE, RET)	WRD_IS_NULL_3(VALUE, wasnull, RET)
#define WRD_IS_NULL_1(VALUE)		WRD_IS_NULL_2(VALUE, wasnull)
#define WRD_IS_NULL(...) 			WRD_OVERLOAD(WRD_IS_NULL, __VA_ARGS__)

#define _ARE_NULL(VALUE, RET)		WRD_IS_NULL(VALUE, RET)
#define WRD_ARE_NULL(RET, ...)		NE_EACH_EXPAND(_ARE_NULL, RET, __VA_ARGS__)

#define WRD_IS_THIS_1(TYPE)			WRD_IS_NULL_3(*this, wasnull, nulr<TYPE>())
#define WRD_IS_THIS_0()				WRD_IS_THIS_1(This)
#define WRD_IS_THIS(...) 			WRD_OVERLOAD(WRD_IS_THIS, __VA_ARGS__)

#define WRD_IS_SUPER_1(call)        		if(Super:: call ) return wassuperfail.warn("");
#define WRD_IS_SUPER_2(res, call)			WRD_IS_SUPER_3(res, call, "")
#define WRD_IS_SUPER_3(res, call, msg)			\
	{											\
		Res& res = Super:: call ;    			\
	    if(res) return wassuperfail.warn(#msg);	\
	}
#define WRD_IS_SUPER(...)					WRD_OVERLOAD(WRD_IS_SUPER, __VA_ARGS__)

#define WRD_IS_CONST(RET)		\
	if((this->isConst())) {		\
		wascancel.warn(#RET);	\
		return RET;				\
	}

#define WRD_ASSERT_4(expr, ret, dump, msg)  \
    if( !(expr) )                            \
        return ret.dump(msg);
#define WRD_ASSERT_3(expr, ret, msg)		WRD_ASSERT_4(expr, ret, warn, msg)
#define WRD_ASSERT_2(expr, ret)				WRD_ASSERT_4(expr, ret, warn, "")
#define WRD_ASSERT_1(expr)                  WRD_ASSERT_4(expr, waswrongop, warn, "")
#define WRD_ASSERT(...)                    	WRD_OVERLOAD(WRD_ASSERT, __VA_ARGS__)

#define WRD_IS_RES_5(expr, ret, chk, dump, msg) \
    {                                          	\
        const Res& res = expr;              	\
        WRD_ASSERT(!(res.chk), ret, dump, msg)    	\
   }
#define WRD_IS_RES_4(expr, chk, dump, msg)  WRD_IS_RES_5(expr, res, chk, dump, msg)
#define WRD_IS_RES_3(expr, chk, msg)        WRD_IS_RES_5(expr, res, chk, warn, msg)
#define WRD_IS_RES_2(expr, chk)            	WRD_IS_RES_5(expr, res, chk, warn, #expr)
#define WRD_IS_RES(...)                    	WRD_OVERLOAD(WRD_IS_RES, __VA_ARGS__)

#define WRD_IS_WARN_3(expr, ret, msg)      	WRD_IS_RES_5(expr, ret, isWarn(), warn, msg)
#define WRD_IS_WARN_2(expr, ret)            WRD_IS_RES_5(expr, ret, isWarn(), warn, #expr)
#define WRD_IS_WARN_1(expr)                	WRD_IS_RES_2(expr, isWarn())
#define WRD_IS_WARN(...)                    WRD_OVERLOAD(WRD_IS_WARN, __VA_ARGS__)

#define WRD_IS_ERR_3(expr, ret, msg)        WRD_IS_RES_5(expr, ret, isErr(), err, msg)
#define WRD_IS_ERR_2(expr, ret)            	WRD_IS_RES_5(expr, ret, isErr(), err, #expr)
#define WRD_IS_ERR_1(expr)                  WRD_IS_RES_2(expr, isErr())
#define WRD_IS_ERR(...)                    	WRD_OVERLOAD(WRD_IS_ERR, __VA_ARGS__)
#define WRD_IS_GOOD_3(expr, ret, msg)      	WRD_IS_RES_5(expr, ret, isGood(), info, msg)
#define WRD_IS_GOOD_2(expr, ret)            WRD_IS_RES_5(expr, ret, isGood(), info, #expr)	
#define WRD_IS_GOOD_1(expr)              	WRD_IS_RES_2(expr, isGood())
#define WRD_IS_GOOD(...)                    WRD_OVERLOAD(WRD_IS_GOOD, __VA_ARGS__)

#define _CLASS_BASE()																		\
    public:																					\
        virtual const Class& getClass() const { return getClassStatic(); }					\
        TStrong<This> clone() const { return TStrong<This>(_clone().down<This>()); }		\
        static WRD_LAZY_METHOD_4(const Class&, getClassStatic, WRD_VOID(), TClass<This>)	\
		static Res& onInitNodes(Container& tray) { return /*TODO: impl */wasgood; }	\
	protected:																				\
		virtual TStrong<Instance> _clone() const { return TCloner<This>::clone(*this); }	\
	private:
#define WRD_CLASS_2(THIS, SUPER)\
    WRD_INHERIT_2(THIS, SUPER) 	\
    _CLASS_BASE()
#define WRD_CLASS_1(THIS)		\
    WRD_INHERIT_1(THIS)			\
    _CLASS_BASE()
#define WRD_CLASS(...) 			WRD_OVERLOAD(WRD_CLASS, __VA_ARGS__)

/// This macros, DECLARE, DEFINE, will be used for which can't dependent to TClass and TStrong and Instance.
///	mostly, those are for base classes of them which correspond to will be used for internal usage only.
///
///	please refer class @ref MetaBean if want to know why I defined nestedclass at this macro.
#define _CLASS_DECL_BASE()								\
	private:											\
		template <typename> friend class TClass;		\
		class __wrd_meta_class_bean : public MetaBean {	\
			template <typename> friend class TClass;	\
			static const Str& getNameStatic();			\
			static const Container& getNodesStatic();	\
			static const Classes& getSupersStatic();	\
			static const Classes& getSubsStatic();		\
			static const Class& getSuperStatic();		\
			static wbool isOccupyStatic();				\
			static wbool isADTStatic();					\
			static wbool isTemplateStatic();			\
			static wbool isInitStatic();				\
			static wbool __is_init;						\
		};												\
	public:												\
		virtual const Class& getClass() const;			\
		TStrong<This> clone() const;					\
		static const Class& getClassStatic();			\
		static Res& onInitNodes(Container& tray);		\
	protected:											\
		virtual TStrong<Instance> _clone() const;		\
	private:
#define WRD_CLASS_DECL_2(THIS, SUPER)	\
	WRD_INHERIT_2(THIS, SUPER)			\
	_CLASS_DECL_BASE()
#define WRD_CLASS_DECL_1(THIS)	\
	WRD_INHERIT_1(THIS)			\
	_CLASS_DECL_BASE()
#define WRD_CLASS_DECL(...) WRD_OVERLOAD(WRD_CLASS_DECL, __VA_ARGS__)

///    this macro should be placed at implement file which include header file using DECLARE macro.
#define _WRD_CLASS_DEF_BEAN_1(THIS)	_WRD_CLASS_DEF_BEAN_2(WRD_VOID(), THIS)
#define _WRD_CLASS_DEF_BEAN_2(TEMPL, THIS)																								\
    TEMPL const Str& THIS::__wrd_meta_class_bean::getNameStatic()																		\
    {																																	\
        static Str inner = MetaBean::_getDemangledName(typeid(THIS).name());															\
		return inner;																													\
    }																																	\
	TEMPL WRD_LAZY_METHOD_4(const Class&, THIS::__wrd_meta_class_bean::getSuperStatic, WRD_VOID(), TClass<typename THIS::Super>)		\
	TEMPL WRD_LAZY_METHOD_4(const Container&, THIS::__wrd_meta_class_bean::getNodesStatic, WRD_VOID(), Array)							\
	TEMPL WRD_LAZY_METHOD_4(const Classes&, THIS::__wrd_meta_class_bean::getSupersStatic, WRD_VOID(), Classes)							\
	TEMPL WRD_LAZY_METHOD_4(const Classes&, THIS::__wrd_meta_class_bean::getSubsStatic, WRD_VOID(), Classes)							\
	TEMPL WRD_LAZY_METHOD_5(wbool, THIS::__wrd_meta_class_bean::isOccupyStatic, WRD_VOID(), wbool, TIfSub<THIS WRD_COMMA() Object>::is)	\
	TEMPL WRD_LAZY_METHOD_5(wbool, THIS::__wrd_meta_class_bean::isADTStatic, WRD_VOID(), wbool, TIfADT< THIS >::is)						\
	TEMPL WRD_LAZY_METHOD_5(wbool, THIS::__wrd_meta_class_bean::isTemplateStatic, WRD_VOID(), wbool, TIfTemplate< THIS >::is)			\
	TEMPL wbool THIS::__wrd_meta_class_bean::isInitStatic() { return __is_init || &getNameStatic() == &TClass<Thing>::getNameStatic(); }\
	TEMPL wbool THIS::__wrd_meta_class_bean::__is_init;
#define _WRD_CLASS_DEF_BEAN(...)	WRD_OVERLOAD(_WRD_CLASS_DEF_BEAN, __VA_ARGS__)

#define WRD_CLASS_DEF_1(THIS)        				WRD_CLASS_DEF_2(WRD_VOID(), THIS)
#define WRD_CLASS_DEF_2(TEMPL, THIS)				\
    TEMPL const Class& THIS::getClass() const {		\
		return this->THIS::getClassStatic();		\
    }    											\
    TEMPL TStrong<Instance> THIS::_clone() const {	\
        return TCloner<THIS>::clone(*this);    		\
	}												\
	TEMPL const Class& THIS::getClassStatic() {		\
        static TClass<This> inner;    				\
        return inner;    							\
	}												\
	TEMPL Res& THIS::onInitNodes(Container& tray) {	\
		/*TODO: impl:*/								\
		return wasgood;								\
	}												\
	_WRD_CLASS_DEF_BEAN_2(TEMPL, THIS)				\
	TEMPL WRD_CLASS_INIT(THIS)

#define WRD_CLASS_DEF(...)            			WRD_OVERLOAD(WRD_CLASS_DEF, __VA_ARGS__)

///	WRD_CLASS_INIT makes that given type T is accessible to ClassManager.
///	if user didn't use WRD_CLASS_DEF against one of their classes, should 
///	put this macro at end of where WRD_CLASS used already.
///	
///	@remark	because retriving and stacking info of World::Class is a little
///	bit of smart, it reculsivly keeps doing it to all super classes.
///	so, may putting this macro on most derived class is enough to.
///	
///	if you use this onto template TYPE, add template parameters as prefix.
///		e.g) template <typename T> WRD_CLASS_INIT(MyTemplate<T>)
#define WRD_CLASS_INIT(TYPE)	WRD_INITIATOR(__COUNTER__, (TYPE::getClassStatic();))	\

#define _PUT(exp) _TGet<TypeTrait<decltype(exp)>::Org>::set(exp)
#define _GET(exp) _TGet<TypeTrait<decltype(exp)>::Org>::get()
#define _NULR(exp) nulr<TypeTrait<decltype(exp)>::Org>()
#define WRD_GET_2(e1, e2) _PUT(e1).isNull() ? _NULR(e1.e2) : _PUT(e1.e2)
#define WRD_GET_3(e1, e2, e3) _PUT(e1).isNull() ? _NULR(e1.e2.e3) : (_PUT(e1.e2).isNull() ? _NULR(e1.e2.e3) : _PUT(e1.e2.e3))
#define WRD_GET_4(e1, e2, e3, e4) _PUT(e1).isNull() ? _NULR(e1.e2.e3.e4) : (_PUT(e1.e2).isNull() ? _NULR(e1.e2.e3.e4) : (_PUT(e1.e2.e3).isNull() ? _NULR(e1.e2.e3.e4) : _PUT(e1.e2.e3.e4)))
#define WRD_GET(...)			WRD_OVERLOAD(WRD_GET, __VA_ARGS__)
