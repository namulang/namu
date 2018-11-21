#pragma once

#include "PathedObject.hpp"

namespace WRD
{
    class File : public PathedObject
    {
        friend class Folder;

    public:
        File(const std::string& path = "");
        File(const File* owner, const std::string& name);
        virtual ~File();

    public:
        virtual type_bool initialize();
        virtual type_bool isInitialized() const;
        const std::string& getBaseDirectory() const;
        type_bool isFolder() const;
        type_ubyte getSize() const;
        virtual const File& peek() const;
        virtual const File& next();
        virtual type_bool release();
        const std::string& getName() const;
        type_bool remove();

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
