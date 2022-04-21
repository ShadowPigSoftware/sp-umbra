#include "pltp_block.hpp"

namespace ShadowPig::Umbra {
    PreprocessorLexerTranslationPhaseBlock::Type PreprocessorLexerTranslationPhaseBlock::type() const {
        return _type;
    }
        
    const LexerTokens& PreprocessorLexerTranslationPhaseBlock::tokens() const {
        return _tokens;
    }
}