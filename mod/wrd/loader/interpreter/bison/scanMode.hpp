#pragma once

#include "../../../common.hpp"
#include "../../../ast/clonable.hpp"
#include "../../../type/wtype.hpp"
#include "lowparser.hpp"

namespace wrd {

    class loweventer;

    class scanMode : public typeProvidable, public clonable {
        WRD(INTERFACE(scanMode))

    public:
        virtual wint onScan(loweventer& eventer, YYSTYPE* yylval, YYLTYPE* yylloc, yyscan_t yyscanner) = 0;
    };

    class indentMode;

    class normalMode : public scanMode {
        WRD(CLASS(normalMode, scanMode))

    public:
        wint onScan(loweventer& eventer, YYSTYPE* yylval, YYLTYPE* yylloc, yyscan_t yyscanner) override;
    };

    class indentMode : public scanMode {
        WRD(CLASS(indentMode, scanMode))

    public:
        wint onScan(loweventer& eventer, YYSTYPE* yylval, YYLTYPE* yylloc, yyscan_t yyscanner) override;
    };
}
