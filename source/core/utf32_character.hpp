#pragma once
#include "utf32_character_class.hpp"
#include "utf32_character_constants.hpp"
#include "utf32_character_traits.hpp"

namespace ShadowPig::Umbra {
    class UTF32Character: public UTF32CharacterClass {
    public:
        using Constants = UTF32CharacterConstants;
        using Traits = UTF32CharacterTraits;

        UTF32Character() = default;


        explicit constexpr UTF32Character(uint32_t character): 
            UTF32CharacterClass(character)
        {}

        UTF32Character(const UTF32Character& character) = default;
        UTF32Character(UTF32Character&& character) = default;

        constexpr UTF32Character(const UTF32CharacterClass& character):
            UTF32CharacterClass(character)
        {}

        constexpr UTF32Character(UTF32CharacterClass&& character):
            UTF32CharacterClass(character)
        {}

        UTF32Character& operator=(const UTF32Character& character) = default;
        UTF32Character& operator=(UTF32Character&& character) = default;

        constexpr UTF32Character& operator=(const UTF32CharacterClass& character) {
            return static_cast<UTF32Character&>(UTF32CharacterClass::operator=(character));
        }

        constexpr UTF32Character& operator=(UTF32CharacterClass&& character) {
            return static_cast<UTF32Character&>(UTF32CharacterClass::operator=(character));
        }
    };
}