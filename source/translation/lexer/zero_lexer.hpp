#pragma once

#include "lexer_token.hpp"
#include "hexadecimal_stem_lexer.hpp"
#include "binary_stem_lexer.hpp"

namespace ShadowPig::Umbra {
    class ZeroLexer {
    public:
        ZeroLexer(const NumericTokenTypes& types);
        LexerToken process(UTF32String::PositionIterator& iterator);
    private:
        LexerToken::Type _type;
        HexadecimalStemLexer _hexadecimalStemLexer;
        BinaryStemLexer _binaryStemLexer;
    };
}