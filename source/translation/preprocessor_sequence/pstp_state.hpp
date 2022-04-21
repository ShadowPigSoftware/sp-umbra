#pragma once

#include "core/utf32_string.hpp"

namespace ShadowPig::Umbra {
    class PreprocessorSequenceTranslationPhaseState {
    public:
        struct ProcessCharacterOutput {
            bool process;
            UTF32Character character;    
            PreprocessorSequenceTranslationPhaseState* nextState;
        };

        virtual ~PreprocessorSequenceTranslationPhaseState() = default;

        virtual void enterState() = 0;
        virtual void exitState() = 0;
        virtual ProcessCharacterOutput processCharacter(const UTF32Character& character) = 0;
    };

    using PSTP_State = PreprocessorSequenceTranslationPhaseState;
}
