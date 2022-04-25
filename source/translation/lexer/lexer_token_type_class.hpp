#pragma once

#include <stdint.h>
#include <utility>
#include <iostream>

namespace ShadowPig::Umbra {
    class LexerTokenTypeClass {
    public:
        LexerTokenTypeClass() = default;

    
        explicit constexpr LexerTokenTypeClass(uint32_t value): 
            _value(value)
        {}

        LexerTokenTypeClass(const LexerTokenTypeClass& character) = default;
        LexerTokenTypeClass(LexerTokenTypeClass&& character) = default;

        LexerTokenTypeClass& operator=(const LexerTokenTypeClass& character) = default;
        LexerTokenTypeClass& operator=(LexerTokenTypeClass&& character) = default;

        constexpr uint32_t value() const {return _value;}

        constexpr bool operator == (const LexerTokenTypeClass& type) const {
            return _value == type._value;
        }

        constexpr bool operator != (const LexerTokenTypeClass& type) const {
            return _value != type._value;
        }

        constexpr bool operator < (const LexerTokenTypeClass& type) const {
            return _value < type._value;
        }

        constexpr bool operator <= (const LexerTokenTypeClass& type) const {
            return _value <= type._value;
        }

        constexpr bool operator > (const LexerTokenTypeClass& type) const {
            return _value > type._value;
        }

        constexpr bool operator >= (const LexerTokenTypeClass& type) const {
            return _value >= type._value;
        }
    private:
        uint32_t _value;
    };
}