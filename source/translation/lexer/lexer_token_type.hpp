#pragma once
#include <stdint.h>
#include <iostream>

namespace ShadowPig::Umbra {
    enum class LexerTokenType: uint32_t {
        //Preprocessor
        NonPreprocessorSequence = 0,
        PreprocessorDeclarationAlpha = 1,
        PreprocessorDeclarationWhitespace = 2,

        //Invalid
        Invalid = 0xFFFFFFFF
    };
}

std::ostream& operator << (std::ostream& stream, ShadowPig::Umbra::LexerTokenType type);