#pragma once

#include "IncludeMacro.hpp"
#include <string>

namespace NE
{
    using std::string;

    class File
    {
        friend class Folder;

    public:
        File(const File* owner, const string& name);
        virtual ~File();

    public:
        const string& getName() const;
        const string& getPath() const;
        const string& getBaseDirectory() const;
        type_bool isFolder() const;
        type_ubyte getSize() const;
        type_bool isNull() const;
        virtual void release();
        virtual const File& peek() const;
        virtual const File& next();

    protected:
        static type_bool _isFolder(struct stat& info);
        static struct stat& _getInfo(const string& path);

    protected:
        void _setName(const string& new_name);

    private:
        /// @remark not allowed.
        File& operator=(const File& rhs);
        File(const File& rhs);

    private:
        const File* _owner;
        string _name;
        string _path;
    };
}