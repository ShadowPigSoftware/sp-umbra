#pragma once

#include "pltp_block.hpp"

namespace ShadowPig::Umbra {
    class PreprocessorLexerTranslationPhasePreprocessorImplementationBlock: public PLTP_Block {
    public:
        PreprocessorLexerTranslationPhasePreprocessorImplementationBlock();
        void addToken(const LexerToken& token);
    };

    using PLTP_PreprocessorImplementationBlock = PreprocessorLexerTranslationPhasePreprocessorImplementationBlock;
}