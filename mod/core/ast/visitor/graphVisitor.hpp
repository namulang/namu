#pragma once

#include "visitor.hpp"

namespace namu {

    class graphVisitor : public visitor {
        NAMU(ME(graphVisitor, visitor))

    public:
        void start(node& root) override {
            _frames.push_back(graphFrame {true});
            super::start(root);
        }

        void _drawIndent() {
            for(char* e : _indents)
                std::cout << e;
        }

        void onVisit(info i, node& visitee) override {
            nbool isParentLast = _parentsLast.last();

            indents.push_back((nowFrame.isParentLast ? "    " : "┃    "));
            _drawIndent();

            nbool isLast = &parent.subs().last().get() == &visitee;
            std::cout << (isLast ? "┗━[" : "┣━[") << "]: " << visitee.getType().getName() << " \"" << name << "\"\n";

        }

        void onLeave(info i, node& visitee) override {
            indents.pop_back();
        }

    private:
        std::vector<nbool> _parentsLast;
        std::vector<char*> _indents;
    };
}
