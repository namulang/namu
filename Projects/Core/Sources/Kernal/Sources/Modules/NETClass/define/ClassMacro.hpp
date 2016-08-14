//	---------------------------------------------------------------------------------
//	Name			:	ClassMacro.hpp
//	Comments		:	
//	Relationships	:	
//	Usage			:	
//	Memo			:	
//	Author			:	2016-02-13	kniz
//	---------------------------------------------------------------------------------
#pragma once

//	template class forward declaration:
//		This macro can be included far earlier than derived class of NETClassBase below.
//		See include section of the NETClassBase.hpp file.
namespace NE
{
	template <typename T>
	class NETInterface;
	template <typename T>
	class NETConcreteClass;
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
		static const NEClassBase& getClassStatically()	\
	private:

#define NE_NATIVE_DEFINE_ONLY(NAME)						\
	const NEClassBase& NAME::getClass() const			\
	{													\
		return getClassStatically();					\
	}													\
														\
	const NEClassBase& NAME::getClassStatically()		\
	{													\
		static NETClass<This> inner;					\
														\
		return inner;									\
	}

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

#define NE_DEFINE_INTERFACE_ONLY(NAME)	\
	NE_NATIVE_DEFINE_ONLY(NAME)

#define NE_DEFINE_CLASS_ONLY(NAME)		\
	NE_NATIVE_DEFINE_ONLY(NAME)			\
										\
	NEObject& NAME::clone() const		\
	{									\
		return *(new This(*this));		\
	}