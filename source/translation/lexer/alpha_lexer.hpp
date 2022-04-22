#pragma once

#include "lexer_token.hpp"

namespace ShadowPig::Umbra {
    class AlphaLexer {
    public:
        AlphaLexer(LexerToken::Type type);
        LexerToken process(UTF32String::PositionIterator& iterator);
    private:
        LexerToken::Type _type;
    };
}