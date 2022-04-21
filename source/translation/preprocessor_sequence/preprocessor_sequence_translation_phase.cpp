#include "preprocessor_sequence_translation_phase.hpp"
#include "pstp_state_normal.hpp"
#include "pstp_state_first_dollar.hpp"
#include "pstp_state_second_dollar.hpp"
#include "pstp_state_declaration_block.hpp"
#include "pstp_state_usage_block.hpp"

namespace ShadowPig::Umbra {
    //this is allowed as the states will only store the reference
    PreprocessorSequenceTranslationPhase::PreprocessorSequenceTranslationPhase():
        _normalState(new PSTP_StateNormal(*this)),
        _firstDollarState(new PSTP_StateFirstDollar(*this)),
        _secondDollarState(new PSTP_StateSecondDollar(*this)),
        _declarationBlockState(new PSTP_StateDeclarationBlock(*this)),
        _usageBlockState(new PSTP_StateUsageBlock(*this)),
        _state(_normalState) 
    {
        _state->enterState();
    }

    PreprocessorSequenceTranslationPhase::~PreprocessorSequenceTranslationPhase() {
        _state->exitState();
        delete _normalState;
        delete _firstDollarState;
        delete _secondDollarState;
        delete _declarationBlockState;
        delete _usageBlockState;
    }

    PreprocessorSequenceTranslationPhase::State* PreprocessorSequenceTranslationPhase::normal() const {
        return _normalState;
    }
       
    PreprocessorSequenceTranslationPhase::State* PreprocessorSequenceTranslationPhase::firstDollar() const {
        return _firstDollarState;
    }
    
    PreprocessorSequenceTranslationPhase::State* PreprocessorSequenceTranslationPhase::secondDollar() const {
        return _secondDollarState;
    }
    
    PreprocessorSequenceTranslationPhase::State* PreprocessorSequenceTranslationPhase::declarationBlock() const {
        return _declarationBlockState;
    }
    
    PreprocessorSequenceTranslationPhase::State* PreprocessorSequenceTranslationPhase::usageBlock() const {
        return _usageBlockState;
    }

    void PreprocessorSequenceTranslationPhase::run(const UTF32String& string) {
        for (auto character: string) {
            auto result = processCharacter(character);
            if (result.process) {
                _output += result.character;
            }

        }
    }
        
    const UTF32String& PreprocessorSequenceTranslationPhase::output() const {
        return _output;
    }

    PreprocessorSequenceTranslationPhase::ProcessCharacterOutput PreprocessorSequenceTranslationPhase::processCharacter(const UTF32Character& character) {
        auto result = _state->processCharacter(character);
        if (result.nextState != _state) {
            _state->exitState();
            _state = result.nextState;
            _state->enterState();
        }
        return ProcessCharacterOutput {
            .process = result.process,
            .character = result.character
        };
    }
}

