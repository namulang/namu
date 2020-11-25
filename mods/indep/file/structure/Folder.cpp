#include "Folder.hpp"

namespace wrd
{
	namespace fm
	{
		using namespace std;
        WRD_DEF_THIS(Folder)

		This::Option::Option(wbool is_reculsive) : _is_reculsive(is_reculsive) {}
		wbool This::Option::isReculsive() const { return _is_reculsive; }

		This::Folder(const std::string& new_path) : Super(new_path), _iterator(0), _sub_file(0) {}
		This::Folder(const File* owner, const string& path, Option option) : Super(owner, path), _iterator(0), _sub_file(0), _option(option) {}
		This::Folder(const string& path, Option option) : Super(0, path), _iterator(0), _sub_file(0), _option(option) {}
		This::~Folder() { _release(); }

		wbool This::init()
		{
			if(isInit())
				_release();
			
			_iterator = opendir(getPath().c_str());
			if( ! _iterator)
				std::cout << strerror(errno) << "=opendir(" << getPath().c_str() << ")\n";
			return ! isInit();
		}
		wbool This::isInit() const { return _iterator; }

		const This::Option& This::getOption() const { return _option; }

		const File& This::next()
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

		const File& This::peek() const { return _sub_file ? _sub_file->peek() : *this; }

		wbool This::release()
		{
			_release();
			return Super::release();
		}

		const File* This::_prepare() const
		{
			if(_sub_file && getOption().isReculsive() && _sub_file->isFolder())
				return &_sub_file->next();
			return 0;
		}

		const File* This::_next() const { return _sub_file && getOption().isReculsive() ? &_sub_file->next() : _sub_file; }
		/// @remark not allowed.
		This::Folder(const Folder& rhs) : File(rhs), _iterator(0) { }
		Folder& This::operator=(const Folder& rhs) { return *this; }

		wbool This::_isFiltered(const File& target) const
		{
			if(target.isNull()) return _iterator != 0; // if next() called at least once and there is no target.

			return false; // okay. seems that we found it.
		}

		File* This::_createSubFile(DIR* e)
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

		void This::_release()
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
