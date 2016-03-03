//	---------------------------------------------------------------------------------
//	Name			:	ClassMacro.hpp
//	Comments		:	
//	Relationships	:	
//	Usage			:	
//	Memo			:	
//	Author			:	2016-02-13	kniz
//	---------------------------------------------------------------------------------
#pragma once
#define NE_DECLARE_CLASS(NAME, SUPER, TYPE)					\
	public:													\
		typedef NAME			This;						\
		typedef TYPE<This>	ThisClass;						\
		typedef SUPER			Super;						\
		typedef TYPE<Super>	SuperClass;						\
															\
	public:													\
		virtual const NEClassBase& getClass() const			\
		{													\
			return getClassStatically();					\
		}													\
		const const ThisClass& getClassStatically() const	\
		{													\
			static ThisClass inner;							\
															\
			return inner;									\
		}
#define NE_DECLARE_INTERFACE(NAME, SUPER)					\
	NE_DECLARE_CLASS(NAME, SUPER, NETInterface)
#define NE_DECLARE_CONCRETE_CLASS(NAME, SUPER)				\
	NE_DECLARE_CLASS(NAME, SUPER, NETClass)

#define NE_REGISTER_CLASS(NAME, TYPE)						\
	namespace												\
	{														\
		class NAME##__Initiator								\
		{													\
		public:												\
			NAME##__Initiator()								\
			{												\
				TYPE<NAME>().enroll();					\
			}												\
		};													\
															\
		NAME##__Initiator NAME##__initiator;				\
	}
#define NE_REGISTER_INTERFACE(NAME)							\
	NE_REGISTER_CLASS(NAME, NETInterface)
#define NE_REGISTER_CONCRETE_CLASS(NAME)					\
	NE_REGISTER_CLASS(NAME, NETClass)