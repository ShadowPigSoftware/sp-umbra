#pragma once

#include "utf32_character.hpp"
#include "utf32_string_position_iterator.hpp"
#include <string>
#include <iostream>

namespace ShadowPig::Umbra {
    class UTF32String: public std::basic_string<UTF32Character> {
    public:
        using basic_string::basic_string;
        using PositionIterator = UTF32StringPositionIterator;
    };
}

std::ostream& operator << (std::ostream& stream, const ShadowPig::Umbra::UTF32String& string);
