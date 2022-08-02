#pragma once

#include "validable.hpp"

namespace namu {

    // TODO: entrypoints[== filePath] can be various. but not language.
    struct _wout entrypoint : public validable {
        entrypoint(const std::string& newLang, const std::vector<std::string> newPaths);
        virtual ~entrypoint();

    public:
        wbool isValid() const override;

    public:
        std::string lang;
        std::vector<std::string> paths;
    };
    typedef std::vector<entrypoint> entrypoints;

    struct manifest : public validable {

        static constexpr const wchar* DEFAULT_NAME = "{default}";

        manifest();
        manifest(const std::string& newName);
        manifest(const std::string& newName, const std::string& newFilePath, const std::string& newAuthor,
                const std::string& newVer, const entrypoints& newPoints);
        virtual ~manifest();

        wbool isValid() const override;

    public:
        std::string name; // manifest name should not contain '.'(dot) character.
        std::string filePath;
        std::string author;
        std::string version;
        std::string ver;

        entrypoints points;
    };

    typedef std::vector<manifest> manifests;
}
