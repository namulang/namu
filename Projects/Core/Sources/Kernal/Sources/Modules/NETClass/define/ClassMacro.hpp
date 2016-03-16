//	---------------------------------------------------------------------------------
//	Name			:	ClassMacro.hpp
//	Comments		:	
//	Relationships	:	
//	Usage			:	
//	Memo			:	
//	Author			:	2016-02-13	kniz
//	---------------------------------------------------------------------------------
#pragma once
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
#define NE_NATIVE_DECLARE_CLASS(NAME, SUPER, METACLASS)		\
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

#define NE_DECLARE_INTERFACE(NAME, SUPER)					\
	NE_NATIVE_DECLARE_CLASS(NAME, SUPER, NETInterface)

#define NE_DECLARE_CLASS(NAME, SUPER)						\
	NE_NATIVE_DECLARE_CLASS(NAME, SUPER, NETConcreteClass)	\
															\
	public:													\
		virtual NEObject& clone() const						\
		{													\
			return *(new This(*this));						\
		}													\
	private: