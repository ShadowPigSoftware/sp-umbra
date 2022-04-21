#include "pstp_state_usage_block.hpp"

namespace ShadowPig::Umbra {
    void PSTP_StateUsageBlock::enterState() {
        _braceCount = 1;
    }

    PSTP_StateUsageBlock::ProcessCharacterOutput PSTP_StateUsageBlock::processCharacter(const UTF32Character& character) {
        if (character == UTF32Character::Constants::LeftBrace) {
            ++_braceCount;
        }
        else if (character == UTF32Character::Constants::RightBrace) {
            --_braceCount;
            if (_braceCount == 0) {
                return ProcessCharacterOutput {
                    .process = true,
                    .character = UTF32Character::Constants::EndOfPreprocessorUsage,
                    .nextState = _states.normal()
                };
            }
        }
        return ProcessCharacterOutput {
            .process = true,
            .character = character,
            .nextState = this
        };
    }
}
