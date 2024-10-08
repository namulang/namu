#pragma once

#include "dep.hpp"
#include "_nout.hpp"

namespace nm {
    class arithmeticObj;
    struct visitInfo;
    class node;
    typedef tstr<node> str;
    class src;
    class modifier;
    class baseFunc;
    class param;

    _nout strWrap __convert__(const arithmeticObj& rhs);
    _nout strWrap __convert__(const str& rhs);
    _nout strWrap __convert__(const src& rhs);
    _nout strWrap __convert__(const baseFunc& rhs);
    _nout strWrap __convert__(const param& rhs);
    _nout strWrap __convert__(const visitInfo& rhs);
    _nout strWrap __convert__(const modifier& rhs);
}
