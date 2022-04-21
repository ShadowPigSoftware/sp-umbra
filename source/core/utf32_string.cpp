#include "utf32_string.hpp"

std::ostream& operator << (std::ostream& stream, const ShadowPig::Umbra::UTF32String& string) {
    bool comma = false;
    for (ShadowPig::Umbra::UTF32Character character: string) {
        if (comma) {
            stream << ",";
        } else {
            comma = true;
        }
        stream << character;
    }
    return stream;
}