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
        const char* getName() const override;
        wbool dump(const char* message) override;

    private:
        std::ofstream _file;
        std::string _path;
    };
}
