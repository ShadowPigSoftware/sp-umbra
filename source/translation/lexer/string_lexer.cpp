#include "string_lexer.hpp"

namespace ShadowPig::Umbra {
    StringLexer::StringLexer(LexerToken::Type type):
        _type(type) 
    {}

    LexerToken StringLexer::process(UTF32String::PositionIterator& iterator) {
        UTF32Character character = *iterator;
        UTF32String lexeme;
        uint32_t line = iterator.line();
        uint32_t column = iterator.column();
        while (character != UTF32Character::Constants::EndOfString) {
            lexeme += character;
            ++iterator;
            character = *iterator;
        }
        lexeme += character;
        ++iterator;
        return LexerToken(_type, lexeme, line, column);
    }
}