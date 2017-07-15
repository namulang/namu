#pragma once

#include <dirent.h>
#include "File.hpp"

namespace NE
{
    class Folder : public File
    {
    public:
        class Option
        {
        public:
            Option(type_bool is_reculsive = true);

        public:
            type_bool isReculsive() const;

        private:
            type_bool _is_reculsive;
        };

    public:
        Folder(const File* owner, const string& path, Option option = Option());
        Folder(const string& path, Option option = Option());
        virtual ~Folder();

    public:
        const Option& getOption() const;
        const File& next();
        const File& peek() const;
        virtual void release();

    private:
        const File* _prepare() const;
        const File* _next() const;
        /// @remark not allowed.
        Folder(const Folder& rhs);
        Folder& operator=(const Folder& rhs);
        type_bool _isFiltered(const File& target) const;
        File* _createSubFile(DIR* e);
        void _release();

    private:
        DIR* _iterator;
        File* _sub_file;
        Option _option;
    };
}