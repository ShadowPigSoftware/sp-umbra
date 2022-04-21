#pragma once

#include "pltp_blocks.hpp"
#include "pltp_iterator.hpp"
#include "core/utf32_string.hpp"
#include "translation/lexer/lexer_tokens.hpp"

namespace ShadowPig::Umbra {
    class PreprocessorLexerTranslationPhase {
    public:
        using Blocks = PLTP_Blocks;
        using Block = PLTP_Block;
        using Iterator = PLTP_Iterator;
        void run(const UTF32String& string);
        const Blocks& output() const;
    private:
        Blocks _output;
    };

    using PLTP = PreprocessorLexerTranslationPhase;
}
