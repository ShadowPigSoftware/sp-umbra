#include "utf32_character_traits.hpp"
#include "utf32_character.hpp"

namespace ShadowPig::Umbra {
    bool UTF32CharacterTraits::isAlpha(const UTF32Character& character) {
        return ((character >= UTF32Character::Constants::a) && (character <= UTF32CharacterConstants::z)) ||
            ((character >= UTF32Character::Constants::A) && (character <= UTF32CharacterConstants::Z)) ||
            (character == UTF32Character::Constants::Underscore);
    }

    bool UTF32CharacterTraits::isNumber(const UTF32Character& character) {
        return ((character >= UTF32Character::Constants::Zero) && (character <= UTF32CharacterConstants::Nine));
    }

    bool UTF32CharacterTraits::isWhitespace(const UTF32Character& character) {
        return (character == UTF32Character::Constants::HorizontalTab) ||
            (character == UTF32Character::Constants::VerticalTab) ||
            (character == UTF32Character::Constants::LineFeed) ||
            (character == UTF32Character::Constants::FormFeed) ||
            (character == UTF32Character::Constants::CarriageReturn) ||
            (character == UTF32Character::Constants::Space);
    }
}