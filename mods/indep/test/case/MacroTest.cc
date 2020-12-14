#include "../common/dep.hpp"

namespace wrd { namespace indep {

    TEST(MacroTest, nul) {

        wint a = 5;
        wint* aPtr = &a;
        wint* aNul = WRD_NULL;
        wint& refNul = nulr<wint>();
        wint& refA = *aPtr;

        ASSERT_TRUE(nul(refNul));
        ASSERT_FALSE(nul(refA));
        wbool isNul = nul(aNul);
        ASSERT_TRUE((void*) isNul);
        ASSERT_FALSE(nul(aPtr));
    }
}}
