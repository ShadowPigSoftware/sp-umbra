#pragma once

#include "pstp_state_base.hpp"

namespace ShadowPig::Umbra {
    class PreprocessorSequenceTranslationPhaseStateNormal: public PreprocessorSequenceTranslationPhaseStateBase {
    public:
        using PreprocessorSequenceTranslationPhaseStateBase::PreprocessorSequenceTranslationPhaseStateBase;

        ProcessCharacterOutput processCharacter(const UTF32Character& character) override;
    };

    using PSTP_StateNormal = PreprocessorSequenceTranslationPhaseStateNormal;
}
