#pragma once

#include "generated/ErrorHandler.h"
#include <logger.hpp>

namespace NE
{
    namespace PR
    {
        class PreferencerErrorHandler : public ErrorHandler
        {
        public:
            virtual void handleUnexpectedToken(int expectedKind, const JJString& expectedToken, Token *actual, PreferencerParser *parser) {
                NE_ERROR("#%d [%d:%d] Expecting %s but got %s. We judged it as <%s>", 
                    ++error_count, actual->beginLine, actual->beginColumn, 
                    addUnicodeEscapes(expectedToken).c_str(), addUnicodeEscapes(actual->image).c_str(),
                    getKind(actual->kind)
                );
            }
            virtual void handleParseError(Token *last, Token *unexpected, const JJSimpleString& production, PreferencerParser *parser) {
                NE_ERROR("#%d [%d:%d] Encountered: %s while parsing: %s", 
                    ++error_count, unexpected->beginLine, unexpected->beginColumn, addUnicodeEscapes(unexpected->image).c_str(), production.c_str()
                );
            }
            virtual void handleOtherError(const JJString& message, PreferencerParser *parser) {
                NE_ERROR("#%d Error: %s", message.c_str());
            }
            static const char* getKind(type_int kind) {
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
        };
    }
}