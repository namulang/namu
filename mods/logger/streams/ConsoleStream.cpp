#include "ConsoleStream.hpp"
#include <iostream>

namespace wrd
{
	namespace log
	{
		#define THIS ConsoleStream
		
		const char* THIS::getName() const { return "ConsoleStream"; }
		wbool THIS::dump(const char* message)
		{
			using std::cout;
			if(Super::dump(message)) return true;

			cout << message << "\n";
			return false;
		}
	}
}
