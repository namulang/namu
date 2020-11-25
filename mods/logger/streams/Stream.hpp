#pragma once

#include "../log-commons.hpp"

namespace wrd
{
	namespace log
	{
		class Stream
		{	WRD_DECL_THIS(Stream)
		public:
			Stream();
			virtual ~Stream();

			/// @return true means an error.
			virtual wbool dump(const char* message);
			wbool isNull() const;
			wbool isEnable() const;
			void setEnable(wbool is_enable);
			virtual const char* getName() const = 0;
			virtual wbool init();
			virtual wbool isInit() const;
			virtual wbool release();

		private:
			wbool _is_enable;
		};
	}
}
