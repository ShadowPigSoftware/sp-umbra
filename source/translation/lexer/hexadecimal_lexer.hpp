#pragma once

#include "lexer_token.hpp"
#include "hexadecimal_lexer.hpp"

namespace ShadowPig::Umbra {
    class HexadecimalLexer {
    public:
        HexadecimalLexer(const NumericTokenTypes& types);
        LexerToken process(UTF32String::PositionIterator& iterator, uint32_t line, uint32_t column);
    private:
        LexerToken::Type _type;
    };
}