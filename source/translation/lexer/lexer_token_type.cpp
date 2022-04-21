#include "lexer_token_type.hpp"

std::ostream& operator << (std::ostream& stream, ShadowPig::Umbra::LexerTokenType type) {
    switch (type) {
    case ShadowPig::Umbra::LexerTokenType::NonPreprocessorSequence:
        stream << "NonPreprocessorSequence";
        break;
    case ShadowPig::Umbra::LexerTokenType::PreprocessorImplementationAlpha:
        stream << "PreprocessorImplementationAlpha";
        break;
    case ShadowPig::Umbra::LexerTokenType::Invalid:
        stream << "Invalid";
        break;
    default:
        stream << static_cast<uint32_t>(type);
        break;
    }
    return stream;
}