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
        Folder(const std::string& path = "");
        Folder(const File* owner, const std::string& path, Option option = Option());
        Folder(const std::string& path, Option option = Option());
        virtual ~Folder();

    public:
        virtual type_bool initialize();
        virtual type_bool isInitialized() const;
        const Option& getOption() const;
        const File& next();
        const File& peek() const;
        virtual type_bool release();

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