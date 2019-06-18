#include "../TestManager.hpp"

WRD_TEST_START(LoggerTest)
	Logger& logger = Logger::getInstance();
	
	T(logger.getName() == std::string("Logger"))
	T(logger.getStreamCount() >= 2)
	T(&logger["ConsoleStream"])
	T(&logger["FileLogStream"])

	WRD_DUMP("D", "hello!")
	WRD_WARN("world!")
	WRD_ERROR("this is not error. paradox?")

	class MyStream : public Stream {
	public:
		virtual const char* getName() const { return "MyStream"; }
		virtual wbool dump(const char* message) {
			msg += message;
			return false;
		}
		std::string msg;
	};
	MyStream* cs = new MyStream();
	T( ! logger.pushStream(cs));
	T(logger.getStreamCount() >= 3)
	T(&logger["MyStream"])

	T( ! logger.dump("hello world"))
	T(cs->msg == "hello world")

	WRD_DUMP("D", "hello!")
	WRD_WARN("world!")
	WRD_ERROR("this is not error. paradox?")


	wbool found = false;
	Folder build(".", Folder::Option(false));            
	while( found || ! build.next().isNull())
		if(build.peek().getName().find("logs"))
			found = true;

	T( ! found)
	T( ! logger.dump("let's go on 2nd phase."));

	WRD_WARN("Fatal error! Fatal error! this PC should be infected to a virus immediatly!!!")
	WRD_ERROR("***backstabbing*** It's a joke. Carm down, my master.")
	//T(logger.release()) -> can't call.            

	return "";
WRD_TEST_END(LoggerTest)
