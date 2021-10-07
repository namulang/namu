#include "err.hpp"

namespace wrd {

    WRD_DEF_ME(err)

    const msgMap& err::getErrMsgs() {
        int id = 0;

#define _ON_MSG(TEXT) {id++, TEXT},

        static msgMap inner {
        WRD_EACH(_ON_MSG,
            "unknown", /* is 0 */
            "this expr doesn't have line number info." /* is 1 */
            /* to be continue... */
        )

#undef _ON_MSG

            // msg for TC:
            {BASE_TEST_CODE + 1, "val is 0"},
            {BASE_TEST_CODE + 2, "grade should be positive"},
        };

        return inner;
    }
}
