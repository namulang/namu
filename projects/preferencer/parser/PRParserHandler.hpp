#pragma once

#include "../commons.hpp"
#include "generated/ErrorHandler.h"

namespace NE
{
    class PRParserHandler : public ErrorHandler
    {
    public:
        virtual void handleUnexpectedToken(int expectedKind, const JJString& expectedToken, Token *actual, PRParser *parser);
        virtual void handleParseError(Token *last, Token *unexpected, const JJSimpleString& production, PRParser *parser);
        virtual void handleOtherError(const JJString& message, PRParser *parser);
        static const char* getKind(type_int kind);
    };
}
