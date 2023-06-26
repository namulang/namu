#include "cli.hpp"
using namespace namu;

namespace namu {

    const flags& cli::getFlags() const {
        static flags inner;
        if(inner.size() <= 0) {
            inner.push_back(tstr<flag>(new helpFlag()));
            inner.push_back(tstr<flag>(new fileFlag()));
            inner.push_back(tstr<flag>(new logStructureFlag()));
            inner.push_back(tstr<flag>(new bufferSrcFlag()));
            inner.push_back(tstr<flag>(new verboseFlag()));
        }

        return inner;
    }
}

int main(int argc, char* argv[]) {
    logger::get()["consoleStream"].setEnable(false);

    cli ep;
    flagArgs a;
    for(int n=1; n < argc ;n++)
        a.push_back(argv[n]);

    ep.run(a);
    return ep.getRes();
}
