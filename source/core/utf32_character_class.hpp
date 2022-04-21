#pragma once

#include <stdint.h>
#include <utility>
#include <iostream>

namespace ShadowPig::Umbra {
    class UTF32CharacterClass {
    public:
        UTF32CharacterClass() = default;

        explicit constexpr UTF32CharacterClass(char character): 
            _character(static_cast<uint32_t>(character)),
            _width(1)
        {}

        explicit constexpr UTF32CharacterClass(uint32_t character): 
            _character(character),
            _width(1)
        {}

        explicit constexpr UTF32CharacterClass(uint32_t character, uint32_t width): 
            _character(character),
            _width(width)
        {}

        UTF32CharacterClass(const UTF32CharacterClass& character) = default;
        UTF32CharacterClass(UTF32CharacterClass&& character) = default;

        UTF32CharacterClass& operator=(const UTF32CharacterClass& character) = default;
        UTF32CharacterClass& operator=(UTF32CharacterClass&& character) = default;

        constexpr uint32_t scalar() const {return _character;}
        constexpr uint32_t width() const {return _width;}

        constexpr bool operator == (uint32_t character) const {
            return _character == character;
        }

        constexpr bool operator == (const UTF32CharacterClass& character) const {
            return _character == character._character;
        }

        constexpr bool operator != (const UTF32CharacterClass& character) const {
            return _character != character._character;
        }

        constexpr bool operator < (const UTF32CharacterClass& character) const {
            return _character < character._character;
        }

        constexpr bool operator <= (const UTF32CharacterClass& character) const {
            return _character <= character._character;
        }

        constexpr bool operator > (const UTF32CharacterClass& character) const {
            return _character > character._character;
        }

        constexpr bool operator >= (const UTF32CharacterClass& character) const {
            return _character >= character._character;
        }
    private:
        uint32_t _character;
        uint32_t _width;
    };
}

std::ostream& operator << (std::ostream& stream, const ::ShadowPig::Umbra::UTF32CharacterClass& character);