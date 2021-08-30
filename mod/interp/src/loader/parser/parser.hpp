#pragma once

#include "parserable.hpp"
#include "../../ast/node.hpp"
#include "../verifier/failReport.hpp"
#include "../src/srcTbl.hpp"

namespace wrd {

    class parser : public parserable, typeProvidable {
        WRD_INTERFACE(parser, parserable)

	public:
		parser() { me::rel(); }

    public:
		me& setReport(failReport& report) {
			_report = &report;
			return *this;
		}
		me& setSrcTbl(srcTbl& srcTbl) {
			_srcTbl = &srcTbl;
			return *this;
		}

        str parseFile(const std::string& path) {
            // TODO:
            return _root;
        }
        str parseBuffer(const std::string& buffer);

		virtual void rel() {
			_root.rel();
			_srcTbl = nullptr;
			_report = nullptr;
		}

    protected:
        str& getRootBinder() override {
            return _root;
        }

    private:
        str _root;
        failReport* _report;
		srcTbl* _srcTbl;
    };
}
