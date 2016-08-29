//	---------------------------------------------------------------------------------
//	Name			:	ClassMacro.hpp
//	Comments		:	
//	Relationships	:	
//	Usage			:	
//	Memo			:	
//	Author			:	2016-02-13	kniz
//	---------------------------------------------------------------------------------
#ifdef NE_NATIVE_DEFINE_TEMPLATE_PARAMETERS
#	undef NE_NATIVE_DEFINE_TEMPLATE_PARAMETERS
#endif

#pragma once

#include "../../Includes/Includes.hpp"

//	template class forward declaration:
//		This macro can be included far earlier than derived class of NETClassBase below.
//		See include section of the NETClassBase.hpp file.
namespace NE
{
	class NE_DLL NEClassBase;

	template <typename T>
	class NETInterface;

	template <typename T>
	class NETConcreteClass;

	template <typename T>
	class NETUnknownMetaClass;
}

//	Class Macros:
//		we're providing fully functioned macro only. please don't use macros which have NATIVE 
//		word on its name. that's internal.
//		when you need partial part of these, please code it explicitly for readibility of other 
//		users.
//		we're afraid that too many macros that user should have to remember exist on codes.
//
//		Essentials:
//			Super, MetaClass typedefs are essentials that each classes should contain them in 
//			order to support RTTI. 
//			by defining these, users can template metaclass with NETClass without consideration 
//			that it's a ADT or concrete class.
#define NE_NATIVE_DECLARE_INLINEY(NAME, SUPER, METACLASS)	\
	public:													\
		typedef NAME			This;						\
		typedef SUPER			Super;						\
		typedef METACLASS<NAME>	MetaClass;					\
															\
	public:													\
		virtual const NEClassBase& getClass() const			\
		{													\
			return getClassStatically();					\
		}													\
															\
	public:													\
		static const NEClassBase& getClassStatically()		\
		{													\
			static NETClass<NAME> inner;					\
															\
			return inner;									\
		}													\
	private:

#define NE_NATIVE_DECLARE_ONLY(NAME, SUPER, METACLASS)	\
	public:												\
		typedef NAME			This;					\
		typedef SUPER			Super;					\
		typedef METACLASS<NAME>	MetaClass;				\
														\
	public:												\
		virtual const NEClassBase& getClass() const;	\
														\
	public:												\
		static const NEClassBase& getClassStatically();	\
	private:


#define NE_NATIVE_DEFINE_ONLY_1(NAME)					\
	NE_NATIVE_DEFINE_ONLY_2(NAME, NE_VOID)

#define NE_NATIVE_DEFINE_ONLY_2(NAME, TYPE_PARAMETERS)	\
	TYPE_PARAMETERS										\
	const NEClassBase& NAME::getClass() const			\
	{													\
		return getClassStatically();					\
	}													\
														\
	TYPE_PARAMETERS										\
	const NEClassBase& NAME::getClassStatically()		\
	{													\
		static NETClass<This> inner;					\
														\
		return inner;									\
	}

#define NE_NATIVE_DEFINE_ONLY_4(NAME1, NAME2, PARAM1, PARAM2)	\
	NE_NATIVE_DEFINE_ONLY_2(NE_MACRO_FUNNEL(NAME1, NAME2), NE_MACRO_FUNNEL(PARAM1, PARAM2))

#define NE_NATIVE_DEFINE_ONLY_6(NAME1, NAME2, NAME3, PARAM1, PARAM2, PARAM3)	\
	NE_NATIVE_DEFINE_ONLY_2(NE_MACRO_FUNNEL(NAME1, NAME2, NAME3), NE_MACRO_FUNNEL(PARAM1, PARAM2, PARAM3))

#define NE_NATIVE_DEFINE_ONLY_8(NAME1, NAME2, NAME3, NAME4, PARAM1, PARAM2, PARAM3, PARAM4)	\
	NE_NATIVE_DEFINE_ONLY_2(NE_MACRO_FUNNEL(NAME1, NAME2, NAME3, NAME4), NE_MACRO_FUNNEL(PARAM1, PARAM2, PARAM3, PARAM4))


#define NE_NATIVE_DEFINE_ONLY(...)	\
	NE_MACRO_OVERLOADER(NE_NATIVE_DEFINE_ONLY, __VA_ARGS__)



#define NE_DECLARE_INTERFACE(NAME, SUPER)						\
	NE_NATIVE_DECLARE_INLINEY(NAME, SUPER, NETInterface)



#define NE_DECLARE_INTERFACE_ONLY(NAME, SUPER)					\
	NE_NATIVE_DECLARE_ONLY(NAME, SUPER, NETInterface)



#define NE_DECLARE_CLASS(NAME, SUPER)							\
	NE_NATIVE_DECLARE_INLINEY(NAME, SUPER, NETConcreteClass)	\
																\
	public:														\
		virtual NEObject& clone() const							\
		{														\
			return *(new This(*this));							\
		}														\
	private:

#define NE_DECLARE_CLASS_ONLY(NAME, SUPER)						\
	NE_NATIVE_DECLARE_ONLY(NAME, SUPER, NETConcreteClass)		\
																\
	public:														\
		virtual NEObject& clone() const;						\
	private:



#define NE_DEFINE_INTERFACE_ONLY_1(NAME)					\
	NE_DEFINE_INTERFACE_ONLY_2(NAME, NE_VOID)

#define NE_DEFINE_INTERFACE_ONLY_2(NAME, TYPE_PARAMETERS)	\
	NE_NATIVE_DEFINE_ONLY(NAME, TYPE_PARAMETERS)

#define NE_DEFINE_INTERFACE_ONLY(...)						\
	NE_MACRO_OVERLOADER(NE_DEFINE_INTERFACE_ONLY, __VA_ARGS__)



#define NE_DEFINE_CLASS_ONLY_2(NAME, TYPE_PARAMETERS)		\
	NE_NATIVE_DEFINE_ONLY(NAME, TYPE_PARAMETERS)			\
															\
	TYPE_PARAMETERS											\
	NEObject& NAME::clone() const							\
	{														\
		return *(new This(*this));							\
	}
#define NE_DEFINE_CLASS_ONLY_1(NAME)						\
	NE_DEFINE_CLASS_ONLY_2(NAME, NE_VOID)
#define NE_DEFINE_CLASS_ONLY(...)							\
	NE_MACRO_OVERLOADER(NE_DEFINE_CLASS_ONLY, __VA_ARGS__)