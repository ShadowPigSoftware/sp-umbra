#include "hexadecimal_stem_lexer.hpp"

namespace ShadowPig::Umbra {
    HexadecimalStemLexer::HexadecimalStemLexer(const NumericTokenTypes& types):
        _hexadecimalLexer(types)
    {}

    LexerToken HexadecimalStemLexer::process(UTF32String::PositionIterator& iterator, uint32_t line, uint32_t column) {
        //we know that the current value of the iterator is x,
        //so incremenet the iterator and look at the next value
        ++iterator;
        if (UTF32Character::Traits::isHexadecimal(*iterator)) {
            return _hexadecimalLexer.process(iterator, line, column);
        }
        //TODO: throw an invalid hexadecimal error
        throw 0;

    }
}