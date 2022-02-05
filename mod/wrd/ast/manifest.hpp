#pragma once

#include "../common.hpp"
#include "validable.hpp"

namespace wrd {

    // TODO: entrypoints[== filePath] can be various. but not language.
    struct entrypoint : public validable {

        entrypoint(const std::string& newLang, const std::vector<std::string> newPaths)
            : lang(newLang), paths(newPaths) {}
        virtual ~entrypoint() {}

        wbool isValid() const override {
            return lang != "" && paths.size() > 0;
        }

    public:
        std::string lang;
        std::vector<std::string> paths;
    };
    typedef std::vector<entrypoint> entrypoints;

    struct manifest : public validable {

        static constexpr const wchar* DEFAULT_NAME = "{default}";

        manifest(): name(DEFAULT_NAME), filePath(""), author("unknown"), ver("") {}
        manifest(const std::string& newName): name(newName), filePath(""), author("unknown"), ver("") {}
        manifest(const std::string& newName, const std::string& newFilePath,
            const std::string& newAuthor, const std::string& newVer, const entrypoints& newPoints)
            : name(newName), filePath(newFilePath), author(newAuthor), ver(newVer), points(newPoints) {}

        virtual ~manifest() {}

        wbool isValid() const override {
             if(name == "" || filePath == "" || filePath == "" || author == "" || ver == "")
                 return false;

             for(entrypoint point : points)
                if(!point.isValid()) return false;

            return true;
        }

    public:
        std::string name;
        std::string filePath;
        std::string author;
        std::string version;
        std::string ver;

        entrypoints points;
    };

    typedef std::vector<manifest> manifests;
}
