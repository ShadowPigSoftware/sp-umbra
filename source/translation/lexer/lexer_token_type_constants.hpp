#pragma once

#include "lexer_token_type_class.hpp"

namespace ShadowPig::Umbra {
    class LexerTokenTypeConstants {
    public:
        static constexpr LexerTokenTypeClass NonPreprocessorSequence = LexerTokenTypeClass(0);
        static constexpr LexerTokenTypeClass Invalid = LexerTokenTypeClass(0xFFFFFFFF);

        struct PreprocessorDeclaration {
            static constexpr LexerTokenTypeClass Alpha = LexerTokenTypeClass(0x10000000);
            static constexpr LexerTokenTypeClass Whitespace = LexerTokenTypeClass(0x10000001);
            static constexpr LexerTokenTypeClass String = LexerTokenTypeClass(0x10000002);
            struct Symbol {
                static constexpr LexerTokenTypeClass ExclamationMark = LexerTokenTypeClass(0x10100000);
                static constexpr LexerTokenTypeClass DoubleQuote = LexerTokenTypeClass(0x10100001);
                static constexpr LexerTokenTypeClass Hash = LexerTokenTypeClass(0x10100002);
                static constexpr LexerTokenTypeClass Dollar = LexerTokenTypeClass(0x10100003);
                static constexpr LexerTokenTypeClass Percent = LexerTokenTypeClass(0x10100004);
                static constexpr LexerTokenTypeClass Ampersand = LexerTokenTypeClass(0x10100005);
                static constexpr LexerTokenTypeClass SingleQuote = LexerTokenTypeClass(0x10100006);
                static constexpr LexerTokenTypeClass LeftParenthesis = LexerTokenTypeClass(0x10100007);
                static constexpr LexerTokenTypeClass RightParenthesis = LexerTokenTypeClass(0x10100008);
                static constexpr LexerTokenTypeClass Asterisk = LexerTokenTypeClass(0x10100009);
                static constexpr LexerTokenTypeClass Plus = LexerTokenTypeClass(0x1010000A);
                static constexpr LexerTokenTypeClass Comma = LexerTokenTypeClass(0x1010000B);
                static constexpr LexerTokenTypeClass Minus = LexerTokenTypeClass(0x1010000C);
                static constexpr LexerTokenTypeClass Period = LexerTokenTypeClass(0x1010000D);
                static constexpr LexerTokenTypeClass Slash = LexerTokenTypeClass(0x1010000E);
                static constexpr LexerTokenTypeClass Colon = LexerTokenTypeClass(0x1010000F);
                static constexpr LexerTokenTypeClass Semicolon = LexerTokenTypeClass(0x10100010);
                static constexpr LexerTokenTypeClass LessThan = LexerTokenTypeClass(0x10100011);
                static constexpr LexerTokenTypeClass Equality = LexerTokenTypeClass(0x10100012);
                static constexpr LexerTokenTypeClass GreaterThan = LexerTokenTypeClass(0x10100013);
                static constexpr LexerTokenTypeClass QuestionMark = LexerTokenTypeClass(0x10100014);
                static constexpr LexerTokenTypeClass LeftBracket = LexerTokenTypeClass(0x10100015);
                static constexpr LexerTokenTypeClass Backslash = LexerTokenTypeClass(0x10100016);
                static constexpr LexerTokenTypeClass RightBracket = LexerTokenTypeClass(0x10100017);
                static constexpr LexerTokenTypeClass Caret = LexerTokenTypeClass(0x10100018);
                static constexpr LexerTokenTypeClass Backtick = LexerTokenTypeClass(0x10100019);
                static constexpr LexerTokenTypeClass LeftBrace = LexerTokenTypeClass(0x1010001A);
                static constexpr LexerTokenTypeClass Pipe = LexerTokenTypeClass(0x1010001B);
                static constexpr LexerTokenTypeClass RightBrace = LexerTokenTypeClass(0x1010001C);
                static constexpr LexerTokenTypeClass Tilde = LexerTokenTypeClass(0x1010001D);
                static constexpr LexerTokenTypeClass String = LexerTokenTypeClass(0x1010001E);
            };

            struct Numeric {
                static constexpr LexerTokenTypeClass Zero = LexerTokenTypeClass(0x10200000);
            };
        };
    };
};