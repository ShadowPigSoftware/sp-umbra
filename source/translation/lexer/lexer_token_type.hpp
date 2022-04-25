#pragma once
#include <stdint.h>
#include <iostream>
#include "lexer_token_type_class.hpp"
#include "lexer_token_type_constants.hpp"

namespace ShadowPig::Umbra {
    class LexerTokenType: public LexerTokenTypeClass, public LexerTokenTypeConstants {
    public:
        LexerTokenType() = default;

        explicit constexpr LexerTokenType(uint32_t character): 
            LexerTokenTypeClass(character)
        {}

        LexerTokenType(const LexerTokenType& character) = default;
        LexerTokenType(LexerTokenType&& character) = default;

        constexpr LexerTokenType(const LexerTokenTypeClass& character):
            LexerTokenTypeClass(character)
        {}

        constexpr LexerTokenType(LexerTokenTypeClass&& character):
            LexerTokenTypeClass(character)
        {}

        LexerTokenType& operator=(const LexerTokenType& character) = default;
        LexerTokenType& operator=(LexerTokenType&& character) = default;

        constexpr LexerTokenType& operator=(const LexerTokenTypeClass& character) {
            return static_cast<LexerTokenType&>(LexerTokenTypeClass::operator=(character));
        }

        constexpr LexerTokenType& operator=(LexerTokenTypeClass&& character) {
            return static_cast<LexerTokenType&>(LexerTokenTypeClass::operator=(character));
        }
    };
}

std::ostream& operator << (std::ostream& stream, ShadowPig::Umbra::LexerTokenType type);