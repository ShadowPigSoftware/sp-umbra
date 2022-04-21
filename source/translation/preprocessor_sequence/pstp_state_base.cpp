#include "pstp_state_base.hpp"

namespace ShadowPig::Umbra {
    PreprocessorSequenceTranslationPhaseStateBase::PreprocessorSequenceTranslationPhaseStateBase(const PSTP_States& states):
        _states(states)
    {}

    void PreprocessorSequenceTranslationPhaseStateBase::enterState() {}
    
    void PreprocessorSequenceTranslationPhaseStateBase::exitState() {}
}
