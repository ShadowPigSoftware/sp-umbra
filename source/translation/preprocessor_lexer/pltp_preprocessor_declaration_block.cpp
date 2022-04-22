#include "pltp_preprocessor_declaration_block.hpp"
#include "translation/lexer/alpha_lexer.hpp"
#include "translation/lexer/whitespace_lexer.hpp"
#include "core/utf32_character_traits.hpp"

namespace ShadowPig::Umbra {
    PLTP_PreprocessorDeclarationBlock::PreprocessorLexerTranslationPhasePreprocessorDeclarationBlock() {
        _type = Type::PreprocessorDeclaration;
    }
    
    void PLTP_PreprocessorDeclarationBlock::run(UTF32String::PositionIterator& it) {
        UTF32Character character = *it;
        while (character != UTF32Character::Constants::EndOfPreprocessorDeclaration) {
            if (UTF32CharacterTraits::isAlpha(character)) {
                AlphaLexer lexer(LexerToken::Type::PreprocessorDeclarationAlpha);
                _tokens.push_back(lexer.process(it));
            }
            else if (UTF32CharacterTraits::isWhitespace(character)) {
                WhitespaceLexer lexer(LexerToken::Type::PreprocessorDeclarationWhitespace);
                _tokens.push_back(lexer.process(it));
            }
            else {
                ++it;
            }
            character = *it;
        }
    }
}