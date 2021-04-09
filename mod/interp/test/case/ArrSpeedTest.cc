#include "../common/dep.hpp"
#include <functional>
#include <chrono>

using namespace wrd;
using namespace std;

namespace  {
    void benchMark(string name, int cnt, function<void(void)> func) {
        Logger::get().setEnable(false);

        auto start = chrono::steady_clock::now();
        for(int n=0; n < cnt; n++)
            func();
        auto end = chrono::steady_clock::now();
        auto totalElapsed = end - start;

        Logger::get().setEnable(true);
        WRD_I("[%s]: it took total %d ms.", name.c_str(), totalElapsed / chrono::milliseconds(1));
        Logger::get().setEnable(false);
    }
}

TEST(ArrSpeedTest, testBenchmark) {
    int clc = 0;
    Obj obj;
    benchMark("create narr 100000 times", 100000, [&clc]() {
        NArr ar;
        clc += ((int64_t) &ar) % 2;
    });
    benchMark("create arr 100000 times", 100000, [&clc]() {
        Arr ar;
        clc += ((int64_t) &ar) % 2;
    });

    benchMark("create vector 100000 times", 100000, [&clc]() {
        vector<Node> ar;
        clc += ((int64_t) &ar) % 2;
    });

    benchMark("create obj 100000 times", 100000, [&clc]() {
        Obj ar;
        clc += ((int64_t) &ar) % 2;
    });

    benchMark("create nchain 100000 times", 100000, [&clc]() {
        NChain ar;
        clc += ((int64_t) &ar) % 2;
    });

    benchMark("add narr 100000 times", 100000, [&]() {
        NArr ar;
        ar.add(obj);
        clc += ((int64_t) &ar) % 2;
    });
    benchMark("add arr 100000 times", 100000, [&]() {
        Arr ar;
        ar.add(obj);
        clc += ((int64_t) &ar) % 2;
    });

    benchMark("add vector 100000 times", 100000, [&]() {
        vector<Str> ar;
        ar.push_back(Str(obj));
        clc += ((int64_t) &ar) % 2;
    });

    benchMark("add nchain 100000 times", 100000, [&]() {
        NChain ar;
        ar.add(obj);
        clc += ((int64_t) &ar) % 2;
    });
}
