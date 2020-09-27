#pragma once

#include "PathedObject.hpp"

namespace wrd
{
	namespace fm
	{
		class File : public PathedObject
		{	WRD_INHERIT(File, PathedObject)
			friend class Folder;

		public:
			File(const std::string& path = "");
			File(const File* owner, const std::string& name);
			virtual ~File();

		public:
			virtual wbool init();
			virtual wbool isInit() const;
			const std::string& getBaseDirectory() const;
			wbool isFolder() const;
			wubyte getSize() const;
			virtual const File& peek() const;
			virtual const File& next();
			virtual wbool release();
			const std::string& getName() const;
			wbool remove();

		protected:
			static wbool _isFolder(struct stat& info);
			static struct stat& _getInfo(const std::string& path);
			void _setName(const std::string& new_name);

		private:
			File& operator=(const File& rhs);
			File(const File& rhs);

		private:
			const File* _owner;
			std::string _name;
		};
	}
}
