#include "preprocessor_lexer_translation_phase.hpp"
#include "pltp_preprocessor_implementation_block.hpp"
#include "core/unused.hpp"

namespace ShadowPig::Umbra {
    void PreprocessorLexerTranslationPhase::run(const UTF32String& string) {
        Internal::unused(string);
        PLTP_PreprocessorImplementationBlock block;
        UTF32String lexeme = {UTF32Character::Constants::a};
        block.addToken(LexerToken(LexerToken::Type::PreprocessorImplementationAlpha, lexeme, 1, 4));
        _output.push_back(block);
    }

    const PreprocessorLexerTranslationPhase::Blocks& PreprocessorLexerTranslationPhase::output() const {
        return _output;
    }
}
