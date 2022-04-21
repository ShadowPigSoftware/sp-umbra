#pragma once
#include <stdint.h>
#include <iostream>

namespace ShadowPig::Umbra {
    enum class LexerTokenType: uint32_t {
        //Preprocessor
        NonPreprocessorSequence = 0,
        PreprocessorImplementationAlpha = 1,

        //Invalid
        Invalid = 0xFFFFFFFF
    };
}

std::ostream& operator << (std::ostream& stream, ShadowPig::Umbra::LexerTokenType type);