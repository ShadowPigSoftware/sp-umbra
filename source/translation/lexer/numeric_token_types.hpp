#pragma once

#include "lexer_token_type_class.hpp"

namespace ShadowPig::Umbra {
    class NumericTokenTypes {
    public:
        virtual ~NumericTokenTypes() = default;
        virtual LexerTokenTypeClass zero() const = 0;
        virtual LexerTokenTypeClass decimal() const = 0;
        virtual LexerTokenTypeClass hexadecimal() const = 0;
        virtual LexerTokenTypeClass binary() const = 0;
        virtual LexerTokenTypeClass floating() const = 0;
    };

    template <class TNumeric> class TNumericTokenTypes: public NumericTokenTypes {
    public:
        LexerTokenTypeClass zero() const override {
            return TNumeric::Zero;
        }

        LexerTokenTypeClass decimal() const override {
            return TNumeric::Decimal;
        }

        LexerTokenTypeClass hexadecimal() const {
            return TNumeric::Hexadecimal;
        }

        LexerTokenTypeClass binary() const {
            return TNumeric::Binary;
        }

        LexerTokenTypeClass floating() const {
            return TNumeric::Float;
        }
    };
};