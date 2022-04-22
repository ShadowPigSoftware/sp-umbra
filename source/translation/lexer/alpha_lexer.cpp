#include "alpha_lexer.hpp"

namespace ShadowPig::Umbra {
    AlphaLexer::AlphaLexer(LexerToken::Type type):
        _type(type) 
    {}

    LexerToken AlphaLexer::process(UTF32String::PositionIterator& iterator) {
        UTF32Character character = *iterator;
        UTF32String lexeme;
        uint32_t line = iterator.line();
        uint32_t column = iterator.column();
        while (UTF32Character::Traits::isAlpha(character) || UTF32Character::Traits::isNumber(character)) {
            lexeme += character;
            ++iterator;
            character = *iterator;
        }
        return LexerToken(_type, lexeme, line, column);
    }
}