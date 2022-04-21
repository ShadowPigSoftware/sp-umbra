#pragma once
#include "lexer_token_type.hpp"
#include "core/utf32_string.hpp"

namespace ShadowPig::Umbra {
    class LexerToken {
    public:
        using Type = LexerTokenType;
        using Lexeme = UTF32String;
        using Line = uint32_t;
        using Column = uint32_t;
        LexerToken();
        LexerToken(Type type, const Lexeme& lexeme, Line line, Column column);

        Type type() const;
        const Lexeme& lexeme() const;
        Line line() const;
        Column column() const;

        bool operator == (const LexerToken& other) const;
    private:
        Type _type;
        Lexeme _lexeme;
        Line _line;
        Column _column;
    };
}

std::ostream& operator << (std::ostream& stream, const ShadowPig::Umbra::LexerToken& token);