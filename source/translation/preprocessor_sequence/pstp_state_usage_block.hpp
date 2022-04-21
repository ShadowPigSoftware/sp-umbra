#pragma once

#include "pstp_state_base.hpp"

namespace ShadowPig::Umbra {
    class PreprocessorSequenceTranslationPhaseStateUsageBlock: public PreprocessorSequenceTranslationPhaseStateBase {
    public:
        using PreprocessorSequenceTranslationPhaseStateBase::PreprocessorSequenceTranslationPhaseStateBase;

        void enterState() override;
        ProcessCharacterOutput processCharacter(const UTF32Character& character) override;
    private:
        uint32_t _braceCount;
        bool _insideString;
    };

    using PSTP_StateUsageBlock = PreprocessorSequenceTranslationPhaseStateUsageBlock;
}
