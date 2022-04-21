#include "pltp_preprocessor_implementation_block.hpp"

namespace ShadowPig::Umbra {
    PLTP_PreprocessorImplementationBlock::PreprocessorLexerTranslationPhasePreprocessorImplementationBlock() {
        _type = Type::PreprocessorImplementation;
    }
    
    void PLTP_PreprocessorImplementationBlock::addToken(const LexerToken& token) {
        _tokens.push_back(token);
    }
}