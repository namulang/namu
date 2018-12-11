#pragma once

#include "File.hpp"

namespace wrd
{
	namespace fm
	{
		class Folder : public File
		{	WRD_INHERIT(Folder, File)
		public:
			class Option
			{
			public:
				Option(wbool is_reculsive = true);

			public:
				wbool isReculsive() const;

			private:
				wbool _is_reculsive;
			};

		public:
			Folder(const std::string& path = "");
			Folder(const File* owner, const std::string& path, Option option = Option());
			Folder(const std::string& path, Option option = Option());
			virtual ~Folder();

		public:
			virtual wbool initialize();
			virtual wbool isInitialized() const;
			const Option& getOption() const;
			const File& next();
			const File& peek() const;
			virtual wbool release();

		private:
			const File* _prepare() const;
			const File* _next() const;
			/// @remark not allowed.
			Folder(const Folder& rhs);
			Folder& operator=(const Folder& rhs);
			wbool _isFiltered(const File& target) const;
			File* _createSubFile(DIR* e);
			void _release();

		private:
			DIR* _iterator;
			File* _sub_file;
			Option _option;
		};
	}
}
