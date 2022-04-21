#include "pltp_preprocessor_declaration_block.hpp"
namespace ShadowPig::Umbra {
    PLTP_PreprocessorDeclarationBlock::PreprocessorLexerTranslationPhasePreprocessorDeclarationBlock() {
        _type = Type::PreprocessorDeclaration;
    }
    
    void PLTP_PreprocessorDeclarationBlock::run(PLTP_Iterator& it) {

        UTF32String lexeme;
        uint32_t line = it.line();
        uint32_t column = it.column();
        while (*it != UTF32Character::Constants::EndOfPreprocessorDeclaration) {
            lexeme += *it;
            ++it;
        }
        _tokens.push_back(LexerToken(LexerToken::Type::PreprocessorDeclarationAlpha, lexeme, line, column));
    }
}