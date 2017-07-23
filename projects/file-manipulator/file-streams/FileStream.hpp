#pragma once

#include "../file-structures/PathedObject.hpp"
#include <string.h>

using namespace std;

namespace NE
{
    class FileStream : public PathedObject
    {
    public:
        enum Mode
        {
            MODE_TYPE_START = 0,
            READ_ONLY = MODE_TYPE_START,
            OVERWRITE_ONLY,

            MODE_TYPE_END,
            WRITABLE = MODE_TYPE_END,
        };

    public:
        FileStream();
        FileStream(const std::string& new_path);
        virtual ~FileStream();

    public:
        type_bool operator+=(type_int delta);
        type_bool operator-=(type_int delta);
        type_bool operator=(type_int new_position);
        type_int getCursor() const;
        type_int getEndOfFile() const;
        /// @brief  Set cursor of file opening to given new_position.
        /// @param  new_position    If this is negative, setCursor based on the END OF FILE.
        ///                         In "positive" case, calculate based on the START OF FILE.
        type_bool setCursor(type_int new_position);
        type_bool setPath(const std::string& new_path);
        type_bool setPath(const PathedObject& path);
        virtual type_bool isInitialized() const;
        virtual type_bool release();
        type_bool setMode(Mode new_mode);
        Mode getMode() const;
        virtual type_count write(const void* chunks, type_count bytes) = 0;
        virtual type_count read(void* target, type_count bytes) = 0;

    private:        
        FileStream(const PathedObject& object);

    protected:
        Mode _mode;
        FILE* _fd;
    };
}