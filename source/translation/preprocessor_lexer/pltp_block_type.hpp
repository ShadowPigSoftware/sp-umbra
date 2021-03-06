#pragma once

#include <iostream>
namespace ShadowPig::Umbra {
    enum class PreprocessorLexerTranslationPhaseBlockType {
        NonPreprocessor,
        PreprocessorDeclaration,
        PreprocessorUsage
    };

    using PLTP_BlockType = PreprocessorLexerTranslationPhaseBlockType;
}

std::ostream& operator << (std::ostream& stream, ::ShadowPig::Umbra::PLTP_BlockType type);