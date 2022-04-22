#pragma once

#include "pltp_block.hpp"

namespace ShadowPig::Umbra {
    class PreprocessorLexerTranslationPhasePreprocessorDeclarationBlock: public PLTP_Block {
    public:
        PreprocessorLexerTranslationPhasePreprocessorDeclarationBlock();
        void run(UTF32String::PositionIterator& it);
    };

    using PLTP_PreprocessorDeclarationBlock = PreprocessorLexerTranslationPhasePreprocessorDeclarationBlock;
}