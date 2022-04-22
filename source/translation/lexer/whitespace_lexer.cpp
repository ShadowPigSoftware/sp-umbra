#include "whitespace_lexer.hpp"

namespace ShadowPig::Umbra {
    WhitespaceLexer::WhitespaceLexer(LexerToken::Type type):
        _type(type) 
    {}

    LexerToken WhitespaceLexer::process(UTF32String::PositionIterator& iterator) {
        UTF32Character character = *iterator;
        UTF32String lexeme;
        uint32_t line = iterator.line();
        uint32_t column = iterator.column();
        while (UTF32Character::Traits::isWhitespace(character)) {
            lexeme += character;
            ++iterator;
            character = *iterator;
        }
        return LexerToken(_type, lexeme, line, column);
    }
}