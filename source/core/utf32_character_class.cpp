#include "utf32_character_class.hpp"

#include <iomanip>

std::ostream& operator << (std::ostream& stream, const ::ShadowPig::Umbra::UTF32CharacterClass& character) {
    std::ios_base::fmtflags streamFlags(stream.flags());
    stream << "UTF32(0x" << std::hex << std::setw(8) << std::setfill('0') << character.scalar() << ")";
    stream.flags(streamFlags);
    return stream;
}