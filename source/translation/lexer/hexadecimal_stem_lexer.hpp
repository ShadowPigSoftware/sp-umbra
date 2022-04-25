#pragma once

#include "lexer_token.hpp"
#include "hexadecimal_lexer.hpp"

namespace ShadowPig::Umbra {
    class HexadecimalStemLexer {
    public:
        HexadecimalStemLexer(const NumericTokenTypes& types);
        LexerToken process(UTF32String::PositionIterator& iterator, uint32_t line, uint32_t column);
    private:
        HexadecimalLexer _hexadecimalLexer;
    };
}