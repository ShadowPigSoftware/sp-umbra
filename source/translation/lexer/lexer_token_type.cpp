#include "lexer_token_type.hpp"

#define ENUM_CASE(x)    case ShadowPig::Umbra::LexerTokenType::x.value(): \
                            stream << #x; \
                            break

std::ostream& operator << (std::ostream& stream, ShadowPig::Umbra::LexerTokenType type) {
    switch (type.value()) {
    ENUM_CASE(NonPreprocessorSequence);
    ENUM_CASE(PreprocessorDeclaration::Alpha);
    ENUM_CASE(PreprocessorDeclaration::Whitespace);
    ENUM_CASE(PreprocessorDeclaration::String);
    ENUM_CASE(PreprocessorDeclaration::Symbol::ExclamationMark);
    ENUM_CASE(PreprocessorDeclaration::Symbol::DoubleQuote);
    ENUM_CASE(PreprocessorDeclaration::Symbol::Hash);
    ENUM_CASE(PreprocessorDeclaration::Symbol::Dollar);
    ENUM_CASE(PreprocessorDeclaration::Symbol::Percent);
    ENUM_CASE(PreprocessorDeclaration::Symbol::Ampersand);
    ENUM_CASE(PreprocessorDeclaration::Symbol::SingleQuote);
    ENUM_CASE(PreprocessorDeclaration::Symbol::LeftParenthesis);
    ENUM_CASE(PreprocessorDeclaration::Symbol::RightParenthesis);
    ENUM_CASE(PreprocessorDeclaration::Symbol::Asterisk);
    ENUM_CASE(PreprocessorDeclaration::Symbol::Plus);
    ENUM_CASE(PreprocessorDeclaration::Symbol::Comma);
    ENUM_CASE(PreprocessorDeclaration::Symbol::Minus);
    ENUM_CASE(PreprocessorDeclaration::Symbol::Period);
    ENUM_CASE(PreprocessorDeclaration::Symbol::Slash);
    ENUM_CASE(PreprocessorDeclaration::Symbol::Colon);
    ENUM_CASE(PreprocessorDeclaration::Symbol::Semicolon);
    ENUM_CASE(PreprocessorDeclaration::Symbol::LessThan);
    ENUM_CASE(PreprocessorDeclaration::Symbol::Equality);
    ENUM_CASE(PreprocessorDeclaration::Symbol::GreaterThan);
    ENUM_CASE(PreprocessorDeclaration::Symbol::QuestionMark);
    ENUM_CASE(PreprocessorDeclaration::Symbol::LeftBracket);
    ENUM_CASE(PreprocessorDeclaration::Symbol::Backslash);
    ENUM_CASE(PreprocessorDeclaration::Symbol::RightBracket);
    ENUM_CASE(PreprocessorDeclaration::Symbol::Caret);
    ENUM_CASE(PreprocessorDeclaration::Symbol::Backtick);
    ENUM_CASE(PreprocessorDeclaration::Symbol::LeftBrace);
    ENUM_CASE(PreprocessorDeclaration::Symbol::Pipe);
    ENUM_CASE(PreprocessorDeclaration::Symbol::RightBrace);
    ENUM_CASE(PreprocessorDeclaration::Symbol::Tilde);
    ENUM_CASE(PreprocessorDeclaration::Numeric::Zero);
    ENUM_CASE(Invalid);
    default:
        stream << type.value();
        break;
    }
    return stream;
}