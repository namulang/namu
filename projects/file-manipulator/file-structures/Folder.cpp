#include "Folder.hpp"

namespace wrd
{
	namespace fm
	{
		using namespace std;
		#define THIS Folder

		Folder::Option::Option(wbool is_reculsive) : _is_reculsive(is_reculsive) {}
		wbool Folder::Option::isReculsive() const { return _is_reculsive; }

		THIS::THIS(const std::string& new_path) : Super(new_path), _iterator(0), _sub_file(0) {}
		THIS::THIS(const File* owner, const string& path, Option option) : Super(owner, path), _iterator(0), _sub_file(0), _option(option) {}
		THIS::THIS(const string& path, Option option) : Super(0, path), _iterator(0), _sub_file(0), _option(option) {}
		THIS::~THIS() { _release(); }

		wbool THIS::init()
		{
			if(isInit())
				_release();
			
			_iterator = opendir(getPath().c_str());
			if( ! _iterator)
				std::cout << strerror(errno) << "=opendir(" << getPath().c_str() << ")\n";
			return ! isInit();
		}
		wbool THIS::isInit() const { return _iterator; }

		const THIS::Option& THIS::getOption() const { return _option; }

		const File& THIS::next()
		{
			//  main:
			//      prepare start_iterator just after returned before:
			//          if _sub_file is not a folder, we should not call its next():
			//              because File.next() always returns valid value. we'll fall into infinite loops.
			const File* to_return = _prepare();
			while(_isFiltered(*to_return))
			{
				if(_sub_file)
					delete _sub_file;
				_sub_file = _createSubFile(_iterator);
				if( ! _sub_file)
					release();

				to_return = _next();
			}

			return *to_return;
		}

		const File& THIS::peek() const { return _sub_file ? _sub_file->peek() : *this; }

		wbool THIS::release()
		{
			_release();
			return Super::release();
		}

		const File* THIS::_prepare() const
		{
			if(_sub_file && getOption().isReculsive() && _sub_file->isFolder())
				return &_sub_file->next();
			return 0;
		}

		const File* THIS::_next() const { return _sub_file && getOption().isReculsive() ? &_sub_file->next() : _sub_file; }
		/// @remark not allowed.
		THIS::Folder(const Folder& rhs) : File(rhs), _iterator(0) { }
		Folder& THIS::operator=(const Folder& rhs) { return *this; }

		wbool THIS::_isFiltered(const File& target) const
		{
			if(target.isNull()) return _iterator != 0; // if next() called at least once and there is no target.

			return false; // okay. seems that we found it.
		}

		File* THIS::_createSubFile(DIR* e)
		{
			//  pre:
			if( ! e) return 0;


			//  main
			string name;
			do
			{
				struct dirent* file = readdir(e);
				if( ! file)
					return 0;
				name = file->d_name;
			} while(name == "." || name == "..");
			//      gathering info:
			if(_isFolder(_getInfo(getPath() + "/" + name)))
				return new Folder(this, name, _option);
			return new File(this, name);
		}

		void THIS::_release()
		{
			if(_sub_file)
				_sub_file->release();
			delete _sub_file;
			_sub_file = 0;

			if(_iterator)
				closedir(_iterator);
			_iterator = 0;
		}
	}
}
