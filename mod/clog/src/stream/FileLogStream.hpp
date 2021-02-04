#pragma once

#include "Stream.hpp"
#include <fstream>

namespace wrd {

    class FileLogStream : public Stream {
        WRD_DECL_THIS(FileLogStream, Stream)

    public:
        //  FileLogStream:
        FileLogStream();
        FileLogStream(const std::string& new_path);

        wbool setPath(const std::string& new_path);
        const std::string& getPath() const;
        //  Stream:
        virtual const char* getName() const;
        virtual wbool dump(const char* message);

    private:
        std::ofstream _file;
        std::string _path;
    };
}
