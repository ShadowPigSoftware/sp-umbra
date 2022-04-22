#include "pstp_state_second_dollar.hpp"

namespace ShadowPig::Umbra {
    PSTP_StateSecondDollar::ProcessCharacterOutput PSTP_StateSecondDollar::processCharacter(const UTF32Character& character) {
        if (character == UTF32Character::Constants::LeftBrace) {
            return ProcessCharacterOutput {
                .process = true,
                .character = UTF32Character::Constants::StartOfPreprocessorDeclaration,
                .nextState = _states.declarationBlock()
            };
        }
        return ProcessCharacterOutput {
            .process = true,
            .character = character,
            .nextState = this
        };
    }
}
