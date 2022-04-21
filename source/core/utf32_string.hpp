#pragma once

#include "core/utf32_character.hpp"
#include <string>
#include <iostream>

namespace ShadowPig::Umbra {
    using UTF32String = std::basic_string<UTF32Character>;
}

std::ostream& operator << (std::ostream& stream, const ShadowPig::Umbra::UTF32String& string);
