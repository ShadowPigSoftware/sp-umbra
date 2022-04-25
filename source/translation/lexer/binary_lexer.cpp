#include "binary_lexer.hpp"

namespace ShadowPig::Umbra {
    BinaryLexer::BinaryLexer(const NumericTokenTypes& types):
        _type(types.binary())
    {}

    LexerToken BinaryLexer::process(UTF32String::PositionIterator& iterator, uint32_t line, uint32_t column) {
        UTF32Character character = *iterator;
        UTF32String lexeme = {UTF32Character::Constants::Zero, UTF32Character::Constants::b};
        while (UTF32Character::Traits::isBinary(character)) {
            lexeme += character;
            ++iterator;
            character = *iterator;
        }
        return LexerToken(_type, lexeme, line, column);
    }
}