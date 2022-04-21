#pragma once

#include "pstp_state_base.hpp"

namespace ShadowPig::Umbra {
    class PreprocessorSequenceTranslationPhaseStateSecondDollar: public PreprocessorSequenceTranslationPhaseStateBase {
    public:
        using PreprocessorSequenceTranslationPhaseStateBase::PreprocessorSequenceTranslationPhaseStateBase;

        ProcessCharacterOutput processCharacter(const UTF32Character& character) override;
    };

    using PSTP_StateSecondDollar = PreprocessorSequenceTranslationPhaseStateSecondDollar;
}
