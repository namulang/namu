#pragma once

#include "../file-structures/PathedObject.hpp"

namespace WRD
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
            /// @brief  In APPENDABLE mode, you can read/write contents of file freely chaning cursor position.
            ///         And cursor position will be set to EndOfFile.
            ///         if the file tried to open doesn't exists, we creates it for you.
            APPENDABLE = MODE_TYPE_END,
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
        virtual type_bool initialize();
        virtual type_bool isInitialized() const;
        virtual type_bool release();
        type_bool setMode(Mode new_mode);
        Mode getMode() const;
        virtual type_count write(const void* chunks, type_count bytes) = 0;
        virtual type_count read(void* target, type_count bytes) = 0;
        std::string readWhole();
        type_bool isEndOfFile() const;

    private:        
        FileStream(const PathedObject& object);

    protected:
        Mode _mode;
        FILE* _fd;
    };
}
