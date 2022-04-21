#include "preprocessor_lexer_translation_phase.hpp"
#include "pltp_preprocessor_implementation_block.hpp"
#include "core/unused.hpp"

namespace ShadowPig::Umbra {
    void PreprocessorLexerTranslationPhase::run(const UTF32String& string) {
        Internal::unused(string);
        PLTP_PreprocessorImplementationBlock block;
        block.addToken(LexerToken::PreprocessorImplementationAlpha(UTF32String {
            UTF32Character::Constants::a
        }));
        _output.push_back(block);
    }

    const PreprocessorLexerTranslationPhase::Blocks& PreprocessorLexerTranslationPhase::output() const {
        return _output;
    }
}
