#pragma once

#include "parserable.hpp"
#include "../../ast/node.hpp"
#include "../errReport.hpp"

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
    class parser : public parserable, typeProvidable {
        WRD(INTERFACE(parser, parserable))

	public:
		parser() { me::rel(); }

    public:
		me& setReport(errReport& report) {
            _report.bind(report);
			return *this;
		}

        /// @param script is null terminated cstring.
        str parse(const wchar* script);

		virtual void rel();

    protected:
        str& getRootBinder() override {
            return _root;
        }

    private:
        str _root;
        tstr<errReport> _report;
    };
}
