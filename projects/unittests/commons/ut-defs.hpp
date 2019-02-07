#pragma once

#define WRD_INITIATE_CLASS(klass) Initiator<klass> __##klass;
#define WRD_TEST_START(name)									\
	namespace wrd												\
	{															\
		namespace ut											\
		{														\
			class name : public TestCase						\
			{	WRD_INHERIT(name, TestCase)						\
			public:												\
				virtual WRD_LAZY_METHOD(std::string&, getName,	\
					const, std::string, #name)					\
			protected:											\
				virtual std::string _onTest();					\
			};													\
			std::string name::_onTest() 						\
			{

#define WRD_TEST_END(name)										\
			}													\
			WRD_INITIATOR(name, (								\
				TestCase::getTests().push_back(new name());		\
			))													\
		}														\
	}
