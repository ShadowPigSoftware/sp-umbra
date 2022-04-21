#include "pstp_state_normal.hpp"

namespace ShadowPig::Umbra {
    PSTP_StateNormal::ProcessCharacterOutput PSTP_StateNormal::processCharacter(const UTF32Character& character) {
        if (character == UTF32Character::Constants::Dollar) {
            return ProcessCharacterOutput {
                .process = false,
                .character = character,
                .nextState = _states.firstDollar()
            };
        }
        return ProcessCharacterOutput {
            .process = true,
            .character = character,
            .nextState = this
        };
    }
}
