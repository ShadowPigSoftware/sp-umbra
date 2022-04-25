#pragma once

namespace ShadowPig::Umbra {
    class UTF32Character;

    class UTF32CharacterTraits {
    public:
        static bool isAlpha(const UTF32Character& character);
        static bool isNumber(const UTF32Character& character);
        static bool isSymbol(const UTF32Character& character);
        static bool isWhitespace(const UTF32Character& character);
    };
}