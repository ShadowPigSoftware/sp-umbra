#pragma once

#include "utf32_character.hpp"

namespace ShadowPig::Umbra {
    
    class UTF32StringPositionIterator {
    public:
        UTF32StringPositionIterator(const std::basic_string<UTF32Character>& string);

        bool isValid() const;
        const UTF32Character& operator* () const;
        uint32_t line() const;
        uint32_t column() const;

        UTF32StringPositionIterator& operator++();
    private:
        std::basic_string<UTF32Character>::const_iterator _it;
        std::basic_string<UTF32Character>::const_iterator _end;
        uint32_t _line;
        uint32_t _column;
    };
}
