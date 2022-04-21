#pragma once

#include "pstp_state.hpp"
#include "pstp_states.hpp"

namespace ShadowPig::Umbra {
    class PreprocessorSequenceTranslationPhaseStateBase: public PreprocessorSequenceTranslationPhaseState {
    public:
        PreprocessorSequenceTranslationPhaseStateBase(const PSTP_States& states);

        void enterState() override;
        void exitState() override;
    protected:
        const PSTP_States& _states;
    };
}
