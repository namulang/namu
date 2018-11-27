#include "PRParserHandler.hpp"
#include "generated/PRParserConstants.h"

namespace WRD
{
    #define THIS PRParserHandler
    
    void THIS::handleUnexpectedToken(int expectedKind, const JJString& expectedToken, Token *actual, PRParser *parser)
    {
        WRD_ERROR("#%d [%d:%d] Expecting %s but got %s. We judged it as <%s>", 
            ++error_count, actual->beginLine, actual->beginColumn, 
            addUnicodeEscapes(expectedToken).c_str(), addUnicodeEscapes(actual->image).c_str(),
            getKind(actual->kind)
        );
    }
    void THIS::handleParseError(Token *last, Token *unexpected, const JJSimpleString& production, PRParser *parser)
    {
        WRD_ERROR("#%d [%d:%d] Encountered: %s while parsing: %s", 
            ++error_count, unexpected->beginLine, unexpected->beginColumn, addUnicodeEscapes(unexpected->image).c_str(), production.c_str()
        );
    }
    void THIS::handleOtherError(const JJString& message, PRParser *parser) 
    {
        WRD_ERROR("#%d Error: %s", message.c_str());
    }

    const char* THIS::getKind(wint kind) 
    {
        switch(kind) {
            #define _CASE(TYPE) case TYPE: return #TYPE;

            _CASE(_EOF)         _CASE(DOUBLE_QUOTATION) _CASE(EOL)          _CASE(NUMBER)
            _CASE(ALPHABET)     _CASE(SYMBOL)           _CASE(TAB)          _CASE(CLASS)
            _CASE(ASSIGN)       _CASE(STRING)           _CASE(INT)          _CASE(BOOL)
            _CASE(FLOAT)        _CASE(CHAR)             _CASE(BOOL_EXPR)    _CASE(CHAR_EXPR)
            _CASE(FLOAT_EXPR)   _CASE(INT_EXPR)         _CASE(LETTER)       _CASE(IDENTIFIER)
            _CASE(LETTERS)

            #undef _CASE
        default:
            return "UNKNOWN";
        }                
    }
}
