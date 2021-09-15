#pragma once

#include "parserable.hpp"
#include "../../ast/node.hpp"
#include "../failReport.hpp"

namespace wrd {

    class parser : public parserable, typeProvidable {
        WRD(INTERFACE(parser, parserable))

	public:
		parser() { me::rel(); }

    public:
		me& setReport(failReport& report) {
			_report = &report;
			return *this;
		}

        str parseBuffer(const std::string& buffer);

		virtual void rel() {
			_root.rel();
			_report = nullptr;
		}

    protected:
        str& getRootBinder() override {
            return _root;
        }

    private:
        str _root;
        failReport* _report;
    };
}
