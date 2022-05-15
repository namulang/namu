#include "cli.hpp"
using namespace wrd;

namespace wrd {

    const options& cli::getOptions() const {
        static options inner;
        if(inner.size() <= 0) {
            inner.push_back(tstr<option>(new helpOption()));
            inner.push_back(tstr<option>(new fileOption()));
        }

        return inner;
    }
}

int main(int argc, char* argv[]) {

    cli ep;

    args a;
    for(int n=0; n < argc ;n++)
        a.push_back(argv[n]);

    ep.run(a);
    return 0;
}
