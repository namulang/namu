#pragma once

#include "../common.hpp"

namespace wrd {

    struct packFiles {
        std::string lang;
        std::vector<std::string> paths;
    };

    struct manifest {
        std::string name;
        std::string packPath;
        std::string filePath;
        std::string author;
        std::string version;

        packFiles files;
    };
}
