#pragma once

#include "stream.hpp"
#include <fstream>

namespace namu {

    class _nout fileLogStream : public stream {
        NAMU_DECL_ME(fileLogStream, stream)

    public:
        //  fileLogStream:
        fileLogStream();
        explicit fileLogStream(const std::string& new_path);

        nbool setPath(const std::string& new_path);
        const std::string& getPath() const;
        //  stream:
        const char* getName() const override;
        nbool dump(const char* message) override;

    private:
        std::ofstream _file;
        std::string _path;
    };
}
