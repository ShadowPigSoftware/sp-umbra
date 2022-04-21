#include "preprocessor_lexer_translation_phase.hpp"
#include "pltp_preprocessor_declaration_block.hpp"
#include "core/unused.hpp"

namespace ShadowPig::Umbra {
    void PreprocessorLexerTranslationPhase::run(const UTF32String& string) {
        Iterator it(string);

        while (it.isValid()) {
            if (*it == UTF32Character::Constants::StartOfPreprocessorDeclaration) {
                ++it;
                PLTP_PreprocessorDeclarationBlock block;
                block.run(it);
                _output.push_back(block);
            }
            // else if (*it == UTF32Character::Constants::StartOfPreprocessorUsage) {
            //     preprocessorUsage.run(it, end);
            // }
            // else {
            //     nonPreprocessor.run(it, end);
            // }
            ++it;
        }
    }

    const PreprocessorLexerTranslationPhase::Blocks& PreprocessorLexerTranslationPhase::output() const {
        return _output;
    }
}
