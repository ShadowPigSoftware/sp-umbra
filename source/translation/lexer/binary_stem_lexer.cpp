#include "binary_stem_lexer.hpp"

namespace ShadowPig::Umbra {
    BinaryStemLexer::BinaryStemLexer(const NumericTokenTypes& types):
        _binaryLexer(types)
    {}

    LexerToken BinaryStemLexer::process(UTF32String::PositionIterator& iterator, uint32_t line, uint32_t column) {
        //we know that the current value of the iterator is x,
        //so incremenet the iterator and look at the next value
        ++iterator;
        if (UTF32Character::Traits::isBinary(*iterator)) {
            return _binaryLexer.process(iterator, line, column);
        }
        //TODO: throw an invalid hexadecimal error
        throw 0;

    }
}