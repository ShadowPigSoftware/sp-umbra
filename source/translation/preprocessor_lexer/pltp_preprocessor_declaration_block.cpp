#include "pltp_preprocessor_declaration_block.hpp"
#include "translation/lexer/alpha_lexer.hpp"
#include "translation/lexer/whitespace_lexer.hpp"
#include "translation/lexer/symbol_lexer.hpp"
#include "translation/lexer/string_lexer.hpp"
#include "translation/lexer/zero_lexer.hpp"
#include "translation/lexer/decimal_lexer.hpp"
#include "core/utf32_character_traits.hpp"

namespace ShadowPig::Umbra {
    PLTP_PreprocessorDeclarationBlock::PreprocessorLexerTranslationPhasePreprocessorDeclarationBlock() {
        _type = Type::PreprocessorDeclaration;
    }
    
    void PLTP_PreprocessorDeclarationBlock::run(UTF32String::PositionIterator& it) {
        UTF32Character character = *it;
        while (character != UTF32Character::Constants::EndOfPreprocessorDeclaration) {
            if (UTF32CharacterTraits::isAlpha(character)) {
                AlphaLexer lexer(LexerToken::Type::PreprocessorDeclaration::Alpha);
                _tokens.push_back(lexer.process(it));
            }
            else if (UTF32CharacterTraits::isWhitespace(character)) {
                WhitespaceLexer lexer(LexerToken::Type::PreprocessorDeclaration::Whitespace);
                _tokens.push_back(lexer.process(it));
            }
            else if (UTF32CharacterTraits::isSymbol(character)) {
                SymbolLexer lexer(SymbolLexer::preprocessorDeclarationTypeFromCharacter(character));
                _tokens.push_back(lexer.process(it));
            }
            else if (character == UTF32Character::Constants::StartOfString) {
                StringLexer lexer(LexerToken::Type::PreprocessorDeclaration::String);
                _tokens.push_back(lexer.process(it));
            }
            else if (character == UTF32Character::Constants::Zero) {
                ZeroLexer lexer(LexerToken::Type::PreprocessorDeclaration::Numeric::Types {});
                _tokens.push_back(lexer.process(it));
            }
            else if (UTF32CharacterTraits::isNumber(character)) {
                DecimalLexer lexer(LexerToken::Type::PreprocessorDeclaration::Numeric::Decimal);
                _tokens.push_back(lexer.process(it));
            }
            else {
                ++it;
            }
            character = *it;
        }
    }
}