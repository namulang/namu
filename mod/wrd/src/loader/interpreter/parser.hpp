#pragma once

#include "parserable.hpp"
#include "../../ast/node.hpp"
#include "../errReport.hpp"

namespace wrd {

    class parser : public parserable, typeProvidable {
        WRD(INTERFACE(parser, parserable))

	public:
		parser() { me::rel(); }

    public:
		me& setReport(errReport& report) {
			_report = &report;
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
        errReport* _report;
    };
}
