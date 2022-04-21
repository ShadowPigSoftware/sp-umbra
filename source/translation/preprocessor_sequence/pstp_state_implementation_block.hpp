#pragma once

#include "pstp_state_base.hpp"

namespace ShadowPig::Umbra {
    class PreprocessorSequenceTranslationPhaseStateImplementationBlock: public PreprocessorSequenceTranslationPhaseStateBase {
    public:
        using PreprocessorSequenceTranslationPhaseStateBase::PreprocessorSequenceTranslationPhaseStateBase;

        void enterState() override;
        ProcessCharacterOutput processCharacter(const UTF32Character& character) override;
    private:
        ProcessCharacterOutput processCharacterInsideString(const UTF32Character& character);
        ProcessCharacterOutput processCharacterOutsideString(const UTF32Character& character);
    private:
        uint32_t _braceCount;
        bool _insideString;
    };

    using PSTP_StateImplementationBlock = PreprocessorSequenceTranslationPhaseStateImplementationBlock;
}
