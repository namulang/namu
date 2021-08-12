#include "../common/dep.hpp"

using namespace wrd;
using namespace std;

TEST(packLoaderTest, testDefaultLoaderInit) {
    const packLoader& systemLoader = wrd::thread::get().getPackLoader();
    ASSERT_FALSE(nul(systemLoader));

    node& pack = systemLoader["samplePack"];
    ASSERT_FALSE(nul(pack));

    ASSERT_EQ(pack.subs().len(), 1);
    node& origin = pack["helloWorld"];
    ASSERT_FALSE(nul(origin));

    {
        func& sayFunc = origin["say"].cast<func>();
        ASSERT_FALSE(nul(sayFunc));

        ASSERT_EQ(sayFunc.getReturnType(), wVoid().getType());
        ASSERT_EQ(sayFunc.getTypes().size(), 1); // 1 for originObj as "me"

        str res = sayFunc.run(narr {&origin} );
        ASSERT_TRUE(res);
        ASSERT_EQ(res->cast<wVoid>(), wVoid());
    }

    {
        func& add = origin["add"].cast<func>();
        ASSERT_FALSE(nul(add));

        const wtypes& argTypes = add.getTypes();
        ASSERT_EQ(argTypes.size(), 3);
        ASSERT_EQ(*argTypes[0], origin.getType());
        ASSERT_EQ(*argTypes[1], ttype<wInt>());

        wInt arg1(5);
        str retVal = add.run(narr {&origin, &arg1} ); // should nothing happen
        ASSERT_FALSE(retVal);

        retVal = add.run(narr(origin, wInt(5), wInt(3)));
        ASSERT_TRUE(retVal);
        ASSERT_EQ(retVal->cast<wInt>().get(), 8);
    }
}
