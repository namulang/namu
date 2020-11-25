#pragma once

#include "../structure/PathedObject.hpp"

namespace wrd {
	namespace fm {

		class FileStream : public PathedObject {
            WRD_DECL_THIS(FileStream, PathedObject)

		public:
			enum Mode {
				MODE_TYPE_START = 0,
				READ_ONLY = MODE_TYPE_START,
				OVERWRITE_ONLY,

				MODE_TYPE_END,
				/// @brief  In APPENDABLE mode, you can read/write contents of file freely chaning cursor position.
				///         And cursor position will be set to EndOfFile.
				///         if the file tried to open doesn't exists, we creates it for you.
				APPENDABLE = MODE_TYPE_END,
			};

		public:
			FileStream();
			FileStream(const std::string& new_path);
			virtual ~FileStream();

		public:
			This& operator+=(wint delta);
			This& operator-=(wint delta);
			This& operator=(wint new_position);
			wint getCursor() const;
			wint getEndOfFile() const;
			/// @brief  Set cursor of file opening to given new_position.
			/// @param  new_position    If this is negative, setCursor based on the END OF FILE.
			///                         In "positive" case, calculate based on the START OF FILE.
			wbool setCursor(wint new_position);
			wbool setPath(const std::string& new_path);
			wbool setPath(const PathedObject& path);
			virtual wbool init();
			virtual wbool isInit() const;
			virtual wbool release();
			wbool setMode(Mode new_mode);
			Mode getMode() const;
			virtual wcnt write(const void* chunks, wcnt bytes) = 0;
			virtual wcnt read(void* target, wcnt bytes) = 0;
			std::string readWhole();
			wbool isEndOfFile() const;

		private:
			FileStream(const PathedObject& object);

		protected:
			Mode _mode;
			FILE* _fd;
		};
	}
}
