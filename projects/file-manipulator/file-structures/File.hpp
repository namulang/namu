#pragma once

#include "PathedObject.hpp"

namespace NE
{
    class File : public PathedObject
    {
        friend class Folder;

    public:
        File(const File* owner, const std::string& name);
        virtual ~File();

    public:
        const std::string& getBaseDirectory() const;
        type_bool isFolder() const;
        type_ubyte getSize() const;
        virtual const File& peek() const;
        virtual const File& next();
        virtual void release();
        const std::string& getName() const;

    protected:
        static type_bool _isFolder(struct stat& info);
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