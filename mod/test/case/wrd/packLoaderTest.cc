#include "../../common/dep.hpp"

using namespace wrd;
using namespace std;

TEST(packLoaderTest, testDefaultLoaderInit) {
    const packs& systemPacks = wrd::thread::get().getSystemPacks();
    ASSERT_FALSE(nul(systemPacks));

    node& pak = systemPacks.get<node>([](const node& e) { return e.getName() == "samplePack"; });
    ASSERT_FALSE(nul(pak));

    ASSERT_EQ(pak.subs().len(), 1);
    node& origin = pak["helloWorld"];
    ASSERT_FALSE(nul(origin));
    {
        func& sayFunc = origin["say"].cast<func>();
        ASSERT_FALSE(nul(sayFunc));

        ASSERT_EQ(sayFunc.getEvalType(), wVoid().getType());
        ASSERT_EQ(sayFunc.getParams().len(), 1); // 1 for originObj as "me"

        str res = sayFunc.run(narr {&origin} );
        ASSERT_TRUE(res);
        ASSERT_EQ(res->cast<wVoid>(), wVoid());
    }

    {
        func& add = origin["add"].cast<func>();
        ASSERT_FALSE(nul(add));

        const params& argTypes = add.getParams();
        ASSERT_EQ(argTypes.len(), 3);
        ASSERT_EQ(argTypes[0].getType(), origin.getType());
        ASSERT_EQ(argTypes[1].getType(), ttype<wInt>());

        wInt arg1(5);
        str retVal = add.run(narr {&origin, &arg1} ); // should nothing happen
        ASSERT_FALSE(retVal);

        retVal = add.run(narr(origin, wInt(5), wInt(3)));
        ASSERT_TRUE(retVal);
        ASSERT_EQ(retVal->cast<wInt>().get(), 8);
    }
}
