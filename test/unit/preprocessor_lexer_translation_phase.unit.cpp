#include <spunit>
#include <spunit_macros>

#include "translation/preprocessor_lexer/preprocessor_lexer_translation_phase.hpp"
#include "test-doubles/fake_file_system.hpp"
#include "utility/test_lexer_sequence.hpp"

using LexerToken = ::ShadowPig::Umbra::LexerToken;
using UTF32Character = ::ShadowPig::Umbra::UTF32Character;
using UTF32String = ::ShadowPig::Umbra::UTF32String;

spunitModule {
    fixture("Preprocessor Lexer Translation Phase") {
        scenario("Empty output by default") {
            ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
            expect(phase.output().size()).to.equal(0u);
        }

        scenario("Replaces Preprocessor Implementation Alpha Token") {
            ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::StartOfPreprocessorDeclaration,
                UTF32Character::Constants::a,
                UTF32Character::Constants::EndOfPreprocessorDeclaration,
                UTF32Character::Constants::EndOfUnit
            });
            expect(phase.output().size()).to.equal(1u);
            auto it = phase.output().begin();
            expect(it->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorImplementation);
            ::ShadowPig::Umbra::Test::testLexerSequence(*this, it->tokens(), {
                LexerToken::PreprocessorImplementationAlpha(UTF32String {
                    UTF32Character::Constants::a
                })
            });
        }
    }
}