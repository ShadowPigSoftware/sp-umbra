#include "symbol_lexer.hpp"

namespace ShadowPig::Umbra {
    namespace {
        using TypeMap = std::map<UTF32Character, LexerToken::Type>;
        template <class T> TypeMap makeTypeMap() {
            return {
                {UTF32Character::Constants::ExclamationMark, T::ExclamationMark},
                {UTF32Character::Constants::DoubleQuote, T::DoubleQuote},
                {UTF32Character::Constants::Hash, T::Hash},
                {UTF32Character::Constants::Dollar, T::Dollar},
                {UTF32Character::Constants::Percent, T::Percent},
                {UTF32Character::Constants::Ampersand, T::Ampersand},
                {UTF32Character::Constants::SingleQuote, T::SingleQuote},
                {UTF32Character::Constants::LeftParenthesis, T::LeftParenthesis},
                {UTF32Character::Constants::RightParenthesis, T::RightParenthesis},
                {UTF32Character::Constants::Asterisk, T::Asterisk},
                {UTF32Character::Constants::Plus, T::Plus},
                {UTF32Character::Constants::Comma, T::Comma},
                {UTF32Character::Constants::Minus, T::Minus},
                {UTF32Character::Constants::Period, T::Period},
                {UTF32Character::Constants::Slash, T::Slash},
                {UTF32Character::Constants::Colon, T::Colon},
                {UTF32Character::Constants::Semicolon, T::Semicolon},
                {UTF32Character::Constants::LessThan, T::LessThan},
                {UTF32Character::Constants::Equality, T::Equality},
                {UTF32Character::Constants::GreaterThan, T::GreaterThan},
                {UTF32Character::Constants::QuestionMark, T::QuestionMark},
                {UTF32Character::Constants::LeftBracket, T::LeftBracket},
                {UTF32Character::Constants::Backslash, T::Backslash},
                {UTF32Character::Constants::RightBracket, T::RightBracket},
                {UTF32Character::Constants::Caret, T::Caret},
                {UTF32Character::Constants::Backtick, T::Backtick},
                {UTF32Character::Constants::LeftBrace, T::LeftBrace},
                {UTF32Character::Constants::Pipe, T::Pipe},
                {UTF32Character::Constants::RightBrace, T::RightBrace},
                {UTF32Character::Constants::Tilde, T::Tilde}
            };
        }
    }

    SymbolLexer::SymbolLexer(LexerToken::Type type):
        _type(type) 
    {}

    LexerToken SymbolLexer::process(UTF32String::PositionIterator& iterator) {
        UTF32Character character = *iterator;
        UTF32String lexeme;
        uint32_t line = iterator.line();
        uint32_t column = iterator.column();
        lexeme += character;
        ++iterator;
        return LexerToken(_type, lexeme, line, column);
    }

    LexerToken::Type SymbolLexer::preprocessorDeclarationTypeFromCharacter(const UTF32Character& character) {
        static TypeMap typeMap = makeTypeMap<LexerToken::Type::PreprocessorDeclaration::Symbol>();
        auto it = typeMap.find(character);
        if (it != typeMap.end()) {
            return it->second;
        }
        //TODO: replace this with an actual exception type
        throw 0;
    }
}