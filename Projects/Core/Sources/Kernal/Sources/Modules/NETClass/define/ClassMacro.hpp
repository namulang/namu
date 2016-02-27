//	---------------------------------------------------------------------------------
//	Name			:	ClassMacro.hpp
//	Comments		:	
//	Relationships	:	
//	Usage			:	
//	Memo			:	
//	Author			:	2016-02-13	kniz
//	---------------------------------------------------------------------------------
#pragma once
#define NE_DECLARE_CLASS(NAME, SUPER)						\
	public:													\
		typedef NAME			This;						\
		typedef NETClass<This>	ThisClass;					\
		typedef SUPER			Super;						\
		typedef NETClass<Super>	SuperClass;					\
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

#define NE_REGISTER_CLASS(NAME)								\
	namespace												\
	{														\
		class NAME##__Initiator								\
		{													\
		public:												\
			NAME##__Initiator()								\
			{												\
				NETClass<NAME>().enroll();					\
			}												\
		};													\
															\
		NAME##__Initiator NAME##__initiator;				\
	}