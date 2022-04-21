#pragma once
#include "lexer_token_type.hpp"
#include "core/utf32_string.hpp"

namespace ShadowPig::Umbra {
    class LexerToken {
    public:
        using Type = LexerTokenType;
        using Lexeme = UTF32String;
        LexerToken();
        LexerToken(Type type, const Lexeme& lexeme);

        Type type() const;
        const Lexeme& lexeme() const;

        bool operator == (const LexerToken& other) const;
    public:
        static LexerToken PreprocessorImplementationAlpha(const Lexeme& lexeme);
    private:
        Type _type;
        Lexeme _lexeme;
    };
}

std::ostream& operator << (std::ostream& stream, const ShadowPig::Umbra::LexerToken& token);