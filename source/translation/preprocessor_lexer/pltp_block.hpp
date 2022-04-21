#pragma once

#include "pltp_block_type.hpp"
#include "translation/lexer/lexer_tokens.hpp"

namespace ShadowPig::Umbra {
    class PreprocessorLexerTranslationPhaseBlock {
    public:
        using Type = PLTP_BlockType;
        Type type() const ;
        const LexerTokens& tokens() const;
    protected:
        Type _type;
        LexerTokens _tokens;
    };

    using PLTP_Block = PreprocessorLexerTranslationPhaseBlock;
}