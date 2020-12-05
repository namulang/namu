#pragma once

#include "Stream.hpp"
#include <fstream>

namespace wrd { namespace clog {

    class FileLogStream : public Stream {
        WRD_DECL_THIS(FileLogStream, Stream)

    public:
        FileLogStream();
        FileLogStream(const std::string& new_path);

    public:
        virtual const char* getName() const;
        wbool setPath(const std::string& new_path);
        const std::string& getPath() const;
        virtual wbool dump(const char* message);

    private:
        std::ofstream _file;
        std::string _path;
    };
} }
