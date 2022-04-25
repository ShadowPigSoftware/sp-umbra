#include "hexadecimal_lexer.hpp"

namespace ShadowPig::Umbra {
    HexadecimalLexer::HexadecimalLexer(const NumericTokenTypes& types):
        _type(types.hexadecimal())
    {}

    LexerToken HexadecimalLexer::process(UTF32String::PositionIterator& iterator, uint32_t line, uint32_t column) {
        UTF32Character character = *iterator;
        UTF32String lexeme = {UTF32Character::Constants::Zero, UTF32Character::Constants::x};
        while (UTF32Character::Traits::isHexadecimal(character)) {
            lexeme += character;
            ++iterator;
            character = *iterator;
        }
        return LexerToken(_type, lexeme, line, column);
    }
}