#pragma once

#include "pltp_block.hpp"
#include "pltp_iterator.hpp"

namespace ShadowPig::Umbra {
    class PreprocessorLexerTranslationPhasePreprocessorDeclarationBlock: public PLTP_Block {
    public:
        PreprocessorLexerTranslationPhasePreprocessorDeclarationBlock();
        void run(PLTP_Iterator& it);
    };

    using PLTP_PreprocessorDeclarationBlock = PreprocessorLexerTranslationPhasePreprocessorDeclarationBlock;
}