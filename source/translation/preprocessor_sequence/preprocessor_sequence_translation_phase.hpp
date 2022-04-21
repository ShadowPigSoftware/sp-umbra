#pragma once

#include "core/utf32_string.hpp"
#include "pstp_states.hpp"

namespace ShadowPig::Umbra {
    class PreprocessorSequenceTranslationPhase: public PSTP_States {
    public:
        PreprocessorSequenceTranslationPhase();
        ~PreprocessorSequenceTranslationPhase();
        using States = PSTP_States;
        void run(const UTF32String& string);
        const UTF32String& output() const;
    private:
        using State = PSTP_State;
        State* normal() const override;
        State* firstDollar() const override;
        State* secondDollar() const override;
        State* declarationBlock() const override;
        State* usageBlock() const override;
    private:
        struct ProcessCharacterOutput {
            bool process;
            UTF32Character character;    
        };
        using ProcessCharacterFunction = ProcessCharacterOutput (PreprocessorSequenceTranslationPhase::*)(const UTF32Character&);
        ProcessCharacterOutput processCharacter(const UTF32Character& character);

    private:
        UTF32String _output;
        
        State* _normalState;
        State* _firstDollarState;
        State* _secondDollarState;
        State* _declarationBlockState;
        State* _usageBlockState;
        State* _state;
    };

    using PSTP = PreprocessorSequenceTranslationPhase;
}
