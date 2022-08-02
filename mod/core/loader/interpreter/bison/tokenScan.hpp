#pragma once

#include "../../../ast/clonable.hpp"
#include "../../../type/wtype.hpp"

typedef union YYSTYPE YYSTYPE;
typedef struct lloc YYLTYPE;
typedef void* yyscan_t;

namespace namu {

    class loweventer;

    class _wout tokenScan : public typeProvidable, public clonable {
        WRD(ADT(tokenScan))

    public:
        wint onScan(loweventer& eventer, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner);
        virtual wint onScan(loweventer& eventer, YYSTYPE* yylval, YYLTYPE* loc, yyscan_t yyscanner, wbool& isBypass);
    };

    class _wout normalScan: public tokenScan {
        WRD(CLASS(normalScan, tokenScan))
        friend class loweventer;

    public:
        using super::onScan;
        wint onScan(loweventer& eventer, YYSTYPE* yylval, YYLTYPE* loc, yyscan_t yyscanner, wbool& isBypass) override;

    private:
        static normalScan* _instance;
    };

    class _wout indentScan : public tokenScan {
        WRD(CLASS(indentScan, tokenScan))
        friend class loweventer;

    public:
        using super::onScan;
        wint onScan(loweventer& eventer, YYSTYPE* yylval, YYLTYPE* loc, yyscan_t yyscanner, wbool& isBypass) override;

    private:
        wint _onIndent(loweventer& ev, wcnt col, wint tok);
        wint _onDedent(loweventer& ev, wcnt col, wint tok);

    private:
        static indentScan* _instance;
    };
}
