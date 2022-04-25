#include "zero_lexer.hpp"

namespace ShadowPig::Umbra {
    ZeroLexer::ZeroLexer(const NumericTokenTypes& types):
        _type(types.zero()),
        _hexadecimalStemLexer(types),
        _binaryStemLexer(types)
    {}

    LexerToken ZeroLexer::process(UTF32String::PositionIterator& iterator) {
        //we know that the current value of the iterator is zero,
        //so incremenet the iterator and look at the next value
        uint32_t line = iterator.line();
        uint32_t column = iterator.column();
        ++iterator;
        UTF32Character character = *iterator;
        if (character == UTF32CharacterConstants::x)
        {
            return _hexadecimalStemLexer.process(iterator, line, column);
        } else if (character == UTF32CharacterConstants::b)
        {
            return _binaryStemLexer.process(iterator, line, column);
        }
        UTF32String lexeme = {UTF32Character::Constants::Zero};
        return LexerToken(_type, lexeme, line, column);
    }
}