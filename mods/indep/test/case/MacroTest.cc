#include "../common/dep.hpp"

namespace wrd { namespace indep {

    TEST(MacroTest, NILandNUL) {

        wint a = 5;
        wint* aPtr = &a;
        wint* aNul = WRD_NULL;
        wint& refNil = *aNul;
        wint& refA = *aPtr;

        ASSERT_TRUE(nil(refNil));
        ASSERT_FALSE(nil(refA));
        ASSERT_TRUE(nul(aNul));
        ASSERT_FALSE(nul(aPtr));
    }
}}
