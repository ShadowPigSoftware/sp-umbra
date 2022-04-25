#pragma once

#include "lexer_token.hpp"
#include "binary_lexer.hpp"

namespace ShadowPig::Umbra {
    class BinaryStemLexer {
    public:
        BinaryStemLexer(const NumericTokenTypes& types);
        LexerToken process(UTF32String::PositionIterator& iterator, uint32_t line, uint32_t column);
    private:
        BinaryLexer _binaryLexer;
    };
}