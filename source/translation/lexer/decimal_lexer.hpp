#pragma once

#include "lexer_token.hpp"

namespace ShadowPig::Umbra {
    class DecimalLexer {
    public:
        DecimalLexer(LexerToken::Type type);
        LexerToken process(UTF32String::PositionIterator& iterator);
    private:
        LexerToken::Type _type;
    };
}