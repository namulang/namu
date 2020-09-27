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

#define WRD_TEST_END(name)								\
			}											\
			WRD_INITIATOR(name, (						\
				TestManager::get().put(new name());		\
			))											\
		}												\
	}

#undef WRD_DUMP
#define WRD_DUMP(level, msg, ...) {                                              \
	wrd::log::Logger::getInstance().dumpFormat("[%s] %s " WRD_TAG " %s <%s::%s#%d> " msg,   \
            getHeader().c_str(), wrd::indep::PlatformAPI::createCurrentTime("%b %d %Y  %X").c_str(), \
            level, __FILENAME__, __func__, __LINE__, ##__VA_ARGS__                     \
        );                                                                      \
    }
