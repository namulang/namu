#pragma once

#include "../../../ast/clonable.hpp"
#include "../../../type/ntype.hpp"

typedef union YYSTYPE YYSTYPE;
typedef struct lloc YYLTYPE;
typedef void* yyscan_t;

namespace namu {

    class loweventer;

    class _nout tokenScan : public typeProvidable, public clonable {
        WRD(ADT(tokenScan))

    public:
        nint onScan(loweventer& eventer, YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner);
        virtual nint onScan(loweventer& eventer, YYSTYPE* yylval, YYLTYPE* loc, yyscan_t yyscanner, nbool& isBypass);
    };

    class _nout normalScan: public tokenScan {
        WRD(CLASS(normalScan, tokenScan))
        friend class loweventer;

    public:
        using super::onScan;
        nint onScan(loweventer& eventer, YYSTYPE* yylval, YYLTYPE* loc, yyscan_t yyscanner, nbool& isBypass) override;

    private:
        static normalScan* _instance;
    };

    class _nout indentScan : public tokenScan {
        WRD(CLASS(indentScan, tokenScan))
        friend class loweventer;

    public:
        using super::onScan;
        nint onScan(loweventer& eventer, YYSTYPE* yylval, YYLTYPE* loc, yyscan_t yyscanner, nbool& isBypass) override;

    private:
        nint _onIndent(loweventer& ev, ncnt col, nint tok);
        nint _onDedent(loweventer& ev, ncnt col, nint tok);

    private:
        static indentScan* _instance;
    };
}
