#include "pstp_state_implementation_block.hpp"

namespace ShadowPig::Umbra {
    void PSTP_StateImplementationBlock::enterState() {
        _braceCount = 1;
        _insideString = false;
    }

    PSTP_StateImplementationBlock::ProcessCharacterOutput PSTP_StateImplementationBlock::processCharacter(const UTF32Character& character ) {
        if (_insideString) {
            return processCharacterInsideString(character);
        }
        return processCharacterOutsideString(character);
    }

    PSTP_StateImplementationBlock::ProcessCharacterOutput PSTP_StateImplementationBlock::processCharacterInsideString(const UTF32Character& character) {
        if (character == UTF32Character::Constants::EndOfString) {
            _insideString = false;
        } 
        return ProcessCharacterOutput {
            .process = true,
            .character = character,
            .nextState = this
        };
    }

    PSTP_StateImplementationBlock::ProcessCharacterOutput PSTP_StateImplementationBlock::processCharacterOutsideString(const UTF32Character& character) {
        if (character == UTF32Character::Constants::LeftBrace) {
            ++_braceCount;
        }
        else if (character == UTF32Character::Constants::RightBrace) {
            --_braceCount;
            if (_braceCount == 0) {
                return ProcessCharacterOutput {
                    .process = true,
                    .character = UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    .nextState = _states.normal()
                };
            }
        }
        else if (character == UTF32Character::Constants::StartOfString) {
            _insideString = true;
        }
        
        return ProcessCharacterOutput {
            .process = true,
            .character = character,
            .nextState = this
        };
    }
}