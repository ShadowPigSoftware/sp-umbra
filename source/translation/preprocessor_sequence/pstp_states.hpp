#pragma once

#include "pstp_state.hpp"

namespace ShadowPig::Umbra {
    class PreprocessorSequenceTranslationPhaseStates {
    public:
        virtual ~PreprocessorSequenceTranslationPhaseStates() = default;

        virtual PreprocessorSequenceTranslationPhaseState* normal() const = 0;
        virtual PreprocessorSequenceTranslationPhaseState* firstDollar() const = 0;
        virtual PreprocessorSequenceTranslationPhaseState* secondDollar() const = 0;
        virtual PreprocessorSequenceTranslationPhaseState* implementationBlock() const = 0;
        virtual PreprocessorSequenceTranslationPhaseState* usageBlock() const = 0;
    };

    using PSTP_States = PreprocessorSequenceTranslationPhaseStates;
}
