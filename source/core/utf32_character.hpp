#pragma once
#include "utf32_character_class.hpp"
#include "utf32_character_constants.hpp"

namespace ShadowPig::Umbra {
    class UTF32Character: public UTF32CharacterClass {
    public:
        using Constants = UTF32CharacterConstants;

        constexpr UTF32Character():
            UTF32CharacterClass()
        {}

        explicit constexpr UTF32Character(uint32_t character): 
            UTF32CharacterClass(character)
        {}

        constexpr UTF32Character(const UTF32Character& character):
            UTF32CharacterClass(static_cast<const UTF32CharacterClass&>(character))
        {}

        constexpr UTF32Character(UTF32Character&& character):
            UTF32CharacterClass(static_cast<UTF32CharacterClass&&>(character))
        {}

        constexpr UTF32Character(const UTF32CharacterClass& character):
            UTF32CharacterClass(character)
        {}

        constexpr UTF32Character(UTF32CharacterClass&& character):
            UTF32CharacterClass(character)
        {}

        constexpr UTF32Character& operator=(const UTF32Character& character) {
            return static_cast<UTF32Character&>(UTF32CharacterClass::operator=(character));
        }

        constexpr UTF32Character& operator=(UTF32Character&& character) {
            return static_cast<UTF32Character&>(UTF32CharacterClass::operator=(character));
        }

        constexpr UTF32Character& operator=(const UTF32CharacterClass& character) {
            return static_cast<UTF32Character&>(UTF32CharacterClass::operator=(character));
        }

        constexpr UTF32Character& operator=(UTF32CharacterClass&& character) {
            return static_cast<UTF32Character&>(UTF32CharacterClass::operator=(character));
        }
    };
}

