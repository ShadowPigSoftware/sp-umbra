#include <spunit>
#include <spunit_macros>

#include "translation/preprocessor_lexer/preprocessor_lexer_translation_phase.hpp"
#include "test-doubles/fake_file_system.hpp"

using LexerToken = ::ShadowPig::Umbra::LexerToken;
using LexerTokens = ::ShadowPig::Umbra::LexerTokens;
using UTF32Character = ::ShadowPig::Umbra::UTF32Character;
using UTF32String = ::ShadowPig::Umbra::UTF32String;

spunitModule {
    fixture("Preprocessor Lexer Translation Phase") {
        scenario("Empty output by default") {
            ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
            expect(phase.output().size()).to.equal(0u);
        }

        fixture("Alpha Tokens") {
            scenario("Replaces Preprocessor Declaration Alpha Token (single character)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::a,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclarationAlpha);
                expect(it->lexeme()).to.equal(UTF32String {UTF32Character::Constants::a});
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Alpha Token (different single character)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::P,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclarationAlpha);
                expect(it->lexeme()).to.equal(UTF32String {UTF32Character::Constants::P});
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Alpha Token (multiple characters)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::a, UTF32Character::Constants::b, UTF32Character::Constants::c, UTF32Character::Constants::d,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclarationAlpha);
                expect(it->lexeme()).to.equal(UTF32String {
                    UTF32Character::Constants::a, UTF32Character::Constants::b, UTF32Character::Constants::c, UTF32Character::Constants::d
                });
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Alpha Token (different multiple characters)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::F, UTF32Character::Constants::l, UTF32Character::Constants::A, UTF32Character::Constants::m, UTF32Character::Constants::E,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclarationAlpha);
                expect(it->lexeme()).to.equal(UTF32String {
                    UTF32Character::Constants::F, UTF32Character::Constants::l, UTF32Character::Constants::A, UTF32Character::Constants::m, UTF32Character::Constants::E
                });
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Alpha Token (beginning with underscore)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::Underscore, UTF32Character::Constants::l, UTF32Character::Constants::A, UTF32Character::Constants::m, UTF32Character::Constants::E,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclarationAlpha);
                expect(it->lexeme()).to.equal(UTF32String {
                    UTF32Character::Constants::Underscore, UTF32Character::Constants::l, UTF32Character::Constants::A, UTF32Character::Constants::m, UTF32Character::Constants::E
                });
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Alpha Token (containing underscore)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::Underscore, UTF32Character::Constants::l, UTF32Character::Constants::Underscore, UTF32Character::Constants::m, UTF32Character::Constants::Underscore,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclarationAlpha);
                expect(it->lexeme()).to.equal(UTF32String {
                    UTF32Character::Constants::Underscore, UTF32Character::Constants::l, UTF32Character::Constants::Underscore, UTF32Character::Constants::m, UTF32Character::Constants::Underscore
                });
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Alpha Token (alpha followed by numbers)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::A, UTF32Character::Constants::One, UTF32Character::Constants::Three, UTF32Character::Constants::Five, UTF32Character::Constants::Eight,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclarationAlpha);
                expect(it->lexeme()).to.equal(UTF32String {
                    UTF32Character::Constants::A, UTF32Character::Constants::One, UTF32Character::Constants::Three, UTF32Character::Constants::Five, UTF32Character::Constants::Eight
                });
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Alpha Token (underscore followed by numbers)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::Underscore, UTF32Character::Constants::One, UTF32Character::Constants::Three, UTF32Character::Constants::Five, UTF32Character::Constants::Eight,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclarationAlpha);
                expect(it->lexeme()).to.equal(UTF32String {
                    UTF32Character::Constants::Underscore, UTF32Character::Constants::One, UTF32Character::Constants::Three, UTF32Character::Constants::Five, UTF32Character::Constants::Eight
                });
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Alpha Token (terminates on whitespace)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::Underscore, UTF32Character::Constants::One, UTF32Character::Constants::Space,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(2u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclarationAlpha);
                expect(it->lexeme()).to.equal(UTF32String {
                    UTF32Character::Constants::Underscore, UTF32Character::Constants::One
                });
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }
        }
    }
}