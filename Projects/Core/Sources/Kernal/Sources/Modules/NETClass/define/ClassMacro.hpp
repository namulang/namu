//	---------------------------------------------------------------------------------
//	Name			:	ClassMacro.hpp
//	Comments		:	
//	Relationships	:	
//	Usage			:	
//	Memo			:	
//	Author			:	2016-02-13	kniz
//	---------------------------------------------------------------------------------
#pragma once

#define NE_NATIVE_DECLARE_CLASS_TYPEDEFS(NAME, SUPER, TYPE)	\
	public:													\
		typedef NAME		This;							\
		typedef TYPE<This>	ThisClass;						\
		typedef SUPER		Super;							\
		typedef TYPE<Super>	SuperClass;						\
	private:	//	returns accessor to default.

#define NE_NATIVE_DECLARE_CLASS_HUSKS(NAME, SUPER, TYPE)	\
		NE_NATIVE_DECLARE_CLASS_TYPEDEFS(NAME, SUPER, TYPE)	\
															\
	public:													\
		virtual const NEClassBase& getClass() const			\
		{													\
			return getClassStatically();					\
		}													\
	private:	

#define NE_NATIVE_DECLARE_CLASS(NAME, SUPER, TYPE)			\
		NE_NATIVE_DECLARE_CLASS_HUSKS(NAME, SUPER, TYPE)	\
															\
	public:													\
		static const ThisClass& getClassStatically()		\
		{													\
			static ThisClass inner;							\
															\
			return inner;									\
		}													\
	private:	//	returns accessor to default.

#define NE_DECLARE_INTERFACE(NAME, SUPER)					\
	NE_NATIVE_DECLARE_CLASS(NAME, SUPER, NETInterface)

#define NE_DECLARE_CLASS(NAME, SUPER)						\
	NE_NATIVE_DECLARE_CLASS(NAME, SUPER, NETClass)