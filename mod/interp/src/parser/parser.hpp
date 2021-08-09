#pragma once

#include "parserable.hpp"
#include "../ast/node.hpp"

namespace wrd {

    class parser : public parserable, typeProvidable {
        WRD_INTERFACE(parser, parserable)

    public:
        str parseFile(const std::string& path) {
            // TODO:
            return _root;
        }

        str parseBuffer(const std::string& buffer);

    protected:
        str& getRootBinder() override {
            return _root;
        }

    private:
        str _root;
    };
}
