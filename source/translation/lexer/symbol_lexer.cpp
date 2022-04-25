#include "symbol_lexer.hpp"

namespace ShadowPig::Umbra {
    SymbolLexer::TypeMap SymbolLexer::_typeMap = {
        {UTF32Character::Constants::ExclamationMark, LexerToken::Type::PreprocessorDeclarationExclamationMark},
        {UTF32Character::Constants::DoubleQuote, LexerToken::Type::PreprocessorDeclarationDoubleQuote},
        {UTF32Character::Constants::Hash, LexerToken::Type::PreprocessorDeclarationHash},
        {UTF32Character::Constants::Dollar, LexerToken::Type::PreprocessorDeclarationDollar},
        {UTF32Character::Constants::Percent, LexerToken::Type::PreprocessorDeclarationPercent},
        {UTF32Character::Constants::Ampersand, LexerToken::Type::PreprocessorDeclarationAmpersand},
        {UTF32Character::Constants::SingleQuote, LexerToken::Type::PreprocessorDeclarationSingleQuote},
        {UTF32Character::Constants::LeftParenthesis, LexerToken::Type::PreprocessorDeclarationLeftParenthesis},
        {UTF32Character::Constants::RightParenthesis, LexerToken::Type::PreprocessorDeclarationRightParenthesis},
        {UTF32Character::Constants::Asterisk, LexerToken::Type::PreprocessorDeclarationAsterisk},
        {UTF32Character::Constants::Plus, LexerToken::Type::PreprocessorDeclarationPlus},
        {UTF32Character::Constants::Comma, LexerToken::Type::PreprocessorDeclarationComma},
        {UTF32Character::Constants::Minus, LexerToken::Type::PreprocessorDeclarationMinus},
        {UTF32Character::Constants::Period, LexerToken::Type::PreprocessorDeclarationPeriod},
        {UTF32Character::Constants::Slash, LexerToken::Type::PreprocessorDeclarationSlash},
        {UTF32Character::Constants::Colon, LexerToken::Type::PreprocessorDeclarationColon},
        {UTF32Character::Constants::Semicolon, LexerToken::Type::PreprocessorDeclarationSemicolon},
        {UTF32Character::Constants::LessThan, LexerToken::Type::PreprocessorDeclarationLessThan},
        {UTF32Character::Constants::Equality, LexerToken::Type::PreprocessorDeclarationEquality},
        {UTF32Character::Constants::GreaterThan, LexerToken::Type::PreprocessorDeclarationGreaterThan},
        {UTF32Character::Constants::QuestionMark, LexerToken::Type::PreprocessorDeclarationQuestionMark},
        {UTF32Character::Constants::LeftBracket, LexerToken::Type::PreprocessorDeclarationLeftBracket},
        {UTF32Character::Constants::Backslash, LexerToken::Type::PreprocessorDeclarationBackslash},
        {UTF32Character::Constants::RightBracket, LexerToken::Type::PreprocessorDeclarationRightBracket},
        {UTF32Character::Constants::Caret, LexerToken::Type::PreprocessorDeclarationCaret},
        {UTF32Character::Constants::Backtick, LexerToken::Type::PreprocessorDeclarationBacktick},
        {UTF32Character::Constants::LeftBrace, LexerToken::Type::PreprocessorDeclarationLeftBrace},
        {UTF32Character::Constants::Pipe, LexerToken::Type::PreprocessorDeclarationPipe},
        {UTF32Character::Constants::RightBrace, LexerToken::Type::PreprocessorDeclarationRightBrace},
        {UTF32Character::Constants::Tilde, LexerToken::Type::PreprocessorDeclarationTilde}
    };

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
        auto it = _typeMap.find(character);
        if (it != _typeMap.end()) {
            return it->second;
        }
        //TODO: replace this with an actual exception type
        throw 0;
    }
}