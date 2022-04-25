#include "lexer_token_type.hpp"

#define ENUM_CASE(x)    case ShadowPig::Umbra::LexerTokenType::x: \
                            stream << #x; \
                            break

std::ostream& operator << (std::ostream& stream, ShadowPig::Umbra::LexerTokenType type) {
    switch (type) {
    ENUM_CASE(NonPreprocessorSequence);
    ENUM_CASE(PreprocessorDeclarationAlpha);
    ENUM_CASE(PreprocessorDeclarationWhitespace);
    ENUM_CASE(PreprocessorDeclarationExclamationMark);
    ENUM_CASE(PreprocessorDeclarationDoubleQuote);
    ENUM_CASE(PreprocessorDeclarationHash);
    ENUM_CASE(PreprocessorDeclarationDollar);
    ENUM_CASE(PreprocessorDeclarationPercent);
    ENUM_CASE(PreprocessorDeclarationAmpersand);
    ENUM_CASE(PreprocessorDeclarationSingleQuote);
    ENUM_CASE(PreprocessorDeclarationLeftParenthesis);
    ENUM_CASE(PreprocessorDeclarationRightParenthesis);
    ENUM_CASE(PreprocessorDeclarationAsterisk);
    ENUM_CASE(PreprocessorDeclarationPlus);
    ENUM_CASE(PreprocessorDeclarationComma);
    ENUM_CASE(PreprocessorDeclarationMinus);
    ENUM_CASE(PreprocessorDeclarationPeriod);
    ENUM_CASE(PreprocessorDeclarationSlash);
    ENUM_CASE(PreprocessorDeclarationColon);
    ENUM_CASE(PreprocessorDeclarationSemicolon);
    ENUM_CASE(PreprocessorDeclarationLessThan);
    ENUM_CASE(PreprocessorDeclarationEquality);
    ENUM_CASE(PreprocessorDeclarationGreaterThan);
    ENUM_CASE(PreprocessorDeclarationQuestionMark);
    ENUM_CASE(PreprocessorDeclarationLeftBracket);
    ENUM_CASE(PreprocessorDeclarationBackslash);
    ENUM_CASE(PreprocessorDeclarationRightBracket);
    ENUM_CASE(PreprocessorDeclarationCaret);
    ENUM_CASE(PreprocessorDeclarationBacktick);
    ENUM_CASE(PreprocessorDeclarationLeftBrace);
    ENUM_CASE(PreprocessorDeclarationPipe);
    ENUM_CASE(PreprocessorDeclarationRightBrace);
    ENUM_CASE(PreprocessorDeclarationTilde);
    ENUM_CASE(PreprocessorDeclarationString);
    ENUM_CASE(Invalid);
    default:
        stream << static_cast<uint32_t>(type);
        break;
    }
    return stream;
}