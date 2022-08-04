#pragma once

#include "../../ast/node.hpp"
#include "../errReport.hpp"
#include "loweventer.hpp"

namespace namu {

    /// parser is a class that finally parses the namu file and creates an ast structure.
    /// this has a parser and a scanner created from a parser generator such as bison
    /// internally, and these are called low-level parsers and low-level scanners.
    /// low-level parser/scanner focuses on whether the string given as input matches a
    /// specific grammar, and passes it to the parser when matching.
    /// this 'parser' class creates and returns an appropriate AST structure if it is
    /// matched.
    ///
    /// the reason for constructing a structure like this is to make it easy to replace other
    /// parser generators.
    /// to accomplish it, please note that this parser class should not be dependent to concrete
    /// implementation which was defined at lowparser/scanner.
    ///
    /// lowparser/scanner should be dependent to THIS.
    class slot;
    class _nout parser : public typeProvidable {
        NAMU(ADT(parser, typeProvidable))

    public:
        parser();

    public:
        me& setReport(errReport& report);
        me& setSlot(const slot& tray);
        slot& getSlot();
        const slot& getSlot() const NAMU_UNCONST_FUNC(getSlot())
        obj& getSubPack();
        const obj& getSubPack() const NAMU_UNCONST_FUNC(getSubPack())

        /// @param script is null terminated cstring.
        tstr<obj> parse(const nchar* script);

        virtual void rel();

    private:
        loweventer _eventer;
    };
}
