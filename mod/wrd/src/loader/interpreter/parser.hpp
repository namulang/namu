#pragma once

#include "../../ast/node.hpp"
#include "../errReport.hpp"
#include "tokenDispatcher.hpp"

namespace wrd {

    /// parser is a class that finally parses the wrd file and creates an ast structure.
    /// this has a parser and a scanner created from a parser generator such as bison
    /// internally, and these are called low-level parsers and low-level scanners.
    /// low-level parser/scanner focuses on whether the string given as input matches a
    /// specific grammar, and passes it to the parser when matching.
    /// this 'parser' class creates and returns an appropriate AST structure if it is
    /// matched.
    ///
    /// the reason for configuring this structure is to make it easy to replace other
    /// parser generators.
    class parser : public typeProvidable {
        WRD(INTERFACE(parser, typeProvidable))

	public:
		parser() { me::rel(); }

    public:
		me& setReport(errReport& report) {
            _report.bind(report);
			return *this;
		}

        /// @param script is null terminated cstring.
        str parse(const wchar* script);

        tokenDispatcher& getDispatcher() { return _dispatcher; }
        const tokenDispatcher& getDispatcher() const { return _dispatcher; }
        str& getRoot() { return _root; }
        const str& getRoot() const { return _root; }

		virtual void rel();

    private:
        str _root;
        tokenDispatcher _dispatcher;
        tstr<errReport> _report;
    };
}
