#pragma once

#include "pltp_block.hpp"
#include <list>

namespace ShadowPig::Umbra {
    using PreprocessorLexerTranslationPhaseBlocks = std::list<PLTP_Block>;
    

    using PLTP_Blocks = PreprocessorLexerTranslationPhaseBlocks;
}