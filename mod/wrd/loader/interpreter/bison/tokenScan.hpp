#pragma once

#include "../../../ast/clonable.hpp"
#include "../../../type/wtype.hpp"

typedef union YYSTYPE YYSTYPE;
typedef struct lloc YYLTYPE;
typedef void* yyscan_t;

namespace wrd {

    class loweventer;

    class tokenScan : public typeProvidable, public clonable {
        WRD(INTERFACE(tokenScan))

    public:
        wint onScan(loweventer& eventer, YYSTYPE* val, yyscan_t scanner) {
            wbool dum;
            return onScan(eventer, val, scanner, dum);
        }
        virtual wint onScan(loweventer& eventer, YYSTYPE* yylval, yyscan_t yyscanner, wbool& isBypass);
    };

    class normalScan: public tokenScan {
        WRD(CLASS(normalScan, tokenScan))
        friend class loweventer;

    public:
        using super::onScan;
        wint onScan(loweventer& eventer, YYSTYPE* yylval, yyscan_t yyscanner, wbool& isBypass) override;

    private:
        static normalScan* _instance;
    };

    class indentScan : public tokenScan {
        WRD(CLASS(indentScan, tokenScan))
        friend class loweventer;

    public:
        using super::onScan;
        wint onScan(loweventer& eventer, YYSTYPE* yylval, yyscan_t yyscanner, wbool& isBypass) override;

    private:
        wint _onIndent(loweventer& ev, wcnt col, wint tok);
        wint _onDedent(loweventer& ev, wcnt col, wint tok);

    private:
        static indentScan* _instance;
    };
}
