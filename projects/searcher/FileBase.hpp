#pragma once

#include "IncludeMacro.hpp"
#include <string>
#include <sys/stat.h>
#include <dirent.h>

namespace NE
{
    using std::string;
    /// FileSearcher components:
    ///     Usage:
    ///         Folder searcher("mymy_folder", Option(true));
    ///         while( ! searcher.next().isNull()) {
    ///             File& file = searcher.peek();
    ///                 ... do something ...
    ///         }
    class File
    {
        friend class Folder;

    public:
        File(const File* owner, const string& name) : _owner(owner) { _setName(name); }
        virtual ~File() {}

    public:
        const string& getName() const { return _name; }
        const string& getPath() const { return _path; }
        const string& getBaseDirectory() const
        {
            static const string inner = "";
            if( ! _owner) return inner;

            return _owner->getPath();
        }
        type_bool isFolder() const { return _isFolder(_getInfo(getPath())); }
        type_ubyte getSize() const { return _getInfo(getPath()).st_size; }
        type_bool isNull() const { return ! this; }
        virtual void release()
        {
            // _path.clear();
            // _owner should not be released.
        }
        virtual const File& peek() const { return *this; }
        virtual const File& next() { return *this; }

    protected:
        static type_bool _isFolder(struct stat& info) { return info.st_mode & S_IFDIR; }
        static struct stat& _getInfo(const string& path)
        {
            static struct stat inner = {0, };

            stat(path.c_str(), &inner);
            return inner;
        }

    protected:
        void _setName(const string& new_name)
        {
            _name = new_name;
            _path = _owner ? _owner->getPath() + "\\" + _name : _path = _name;
        }

    private:
        /// @remark not allowed.
        File& operator=(const File& rhs) { return *this; }
        File(const File& rhs) : _owner(0), _path(rhs._path) {}

    private:
        const File* _owner;
        string _name;
        string _path;
    };

    class Folder : public File
    {
    public:
        class Option
        {
        public:
            Option(type_bool is_reculsive = true)
            : _is_reculsive(is_reculsive) {}

        public:
            type_bool isReculsive() const { return _is_reculsive; }

        private:
            type_bool _is_reculsive;
        };

    public:
        Folder(const File* owner, const string& path, Option option = Option()) : File(owner, path), _iterator(0), _sub_file(0), _option(option) {}
        Folder(const string& path, Option option = Option()) : File(0, path), _iterator(0), _sub_file(0), _option(option) {}
        virtual ~Folder() { _release(); }

    public:
        const Option& getOption() const { return _option; }
        const File& next()
        {
            //  pre:
            if( ! _iterator)
                _iterator = opendir(getPath().c_str());


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
        const File& peek() const
        {
            return _sub_file ? _sub_file->peek() : *this;
        }
        virtual void release()
        {
            _release();
            File::release();
        }

    private:
        const File* _prepare() const
        {
            if(_sub_file && getOption().isReculsive() && _sub_file->isFolder())
                return &_sub_file->next();
            return 0;
        }
        const File* _next() const { return _sub_file && getOption().isReculsive() ? &_sub_file->next() : _sub_file; }
        /// @remark not allowed.
        Folder(const Folder& rhs) : File(rhs), _iterator(0) { }
        Folder& operator=(const Folder& rhs) { return *this; }
        type_bool _isFiltered(const File& target) const
        {
            if(target.isNull()) return _iterator != 0; // if next() called at least once and there is no target.

            return false; // okay. seems that we found it.
        }
        File* _createSubFile(DIR* e)
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
            if(_isFolder(_getInfo(getPath() + "\\" + name)))
                return new Folder(this, name, _option);
            return new File(this, name);
        }
        void _release()
        {
            if(_sub_file)
                _sub_file->release();
            delete _sub_file;
            _sub_file = 0;

            if(_iterator)
                closedir(_iterator);
            _iterator = 0;
        }

    private:
        DIR* _iterator;
        File* _sub_file;
        Option _option;
    };
}