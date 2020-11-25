#pragma once

#include "../../indep-common.hpp"
#include "../../macro.hpp"

namespace wrd {
	namespace fm {

		class PathedObject {
            WRD_DECL_THIS(PathedObject)

		public:
			PathedObject();
			PathedObject(const std::string& path);
			PathedObject(const PathedObject& rhs);

		public:
			virtual wbool init() = 0;
			virtual wbool isInit() const = 0;
			const std::string& getPath() const;
			wbool isNull() const;
			virtual wbool release();

		protected:
			wbool _setPath(const std::string& new_path);

		private:
			/// @remark not allowed.
			PathedObject& operator=(const PathedObject& rhs);

		private:
			std::string _path;
		};
	}
}
