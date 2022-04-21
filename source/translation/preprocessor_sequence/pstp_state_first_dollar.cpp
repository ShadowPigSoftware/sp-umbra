#include "pstp_state_first_dollar.hpp"

namespace ShadowPig::Umbra {
    PSTP_StateFirstDollar::ProcessCharacterOutput PSTP_StateFirstDollar::processCharacter(const UTF32Character& character) {
        if (character == UTF32Character::Constants::Dollar) {
            return ProcessCharacterOutput {
                .process = false,
                .character = character,
                .nextState = _states.secondDollar()
            };
        }
        else if (character == UTF32Character::Constants::LeftBrace) {
            return ProcessCharacterOutput {
                .process = true,
                .character = UTF32Character::Constants::StartOfPreprocessorUsage,
                .nextState = _states.usageBlock()
            };
        }
        return ProcessCharacterOutput {
            .process = true,
            .character = character,
            .nextState = this
        };
    }
}
