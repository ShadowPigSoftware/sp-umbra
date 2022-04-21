#include <spunit>
#include <spunit_macros>

#include "translation/preprocessor_sequence/preprocessor_sequence_translation_phase.hpp"
#include "test-doubles/fake_file_system.hpp"
#include "utility/test_character_sequence.hpp"

using UTF32Character = ::ShadowPig::Umbra::UTF32Character;
using UTF32String = ::ShadowPig::Umbra::UTF32String;



spunitModule {
    fixture("Preprocessor Sequence Translation Phase") {
        scenario("Empty output by default") {
            ::ShadowPig::Umbra::PreprocessorSequenceTranslationPhase phase;
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {});
        }

        scenario("Replaces Double Dollar brace \"$${\" with Preprocessor declaration start, and end brace with Preprocessor declaration end") {
            ::ShadowPig::Umbra::PreprocessorSequenceTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::Dollar, UTF32Character::Constants::Dollar, UTF32Character::Constants::LeftBrace,
                UTF32Character::Constants::RightBrace,
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfPreprocessorDeclaration,
                UTF32Character::Constants::EndOfPreprocessorDeclaration,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Replaces Double Dollar brace \"$${\" with Preprocessor declaration start, and end brace with Preprocessor declaration end (containing characters") {
            ::ShadowPig::Umbra::PreprocessorSequenceTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::Dollar, UTF32Character::Constants::Dollar, UTF32Character::Constants::LeftBrace,
                UTF32Character::Constants::A, UTF32Character::Constants::B, UTF32Character::Constants::C,
                UTF32Character::Constants::RightBrace,
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfPreprocessorDeclaration,
                UTF32Character::Constants::A,
                UTF32Character::Constants::B,
                UTF32Character::Constants::C,
                UTF32Character::Constants::EndOfPreprocessorDeclaration,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Double Dollar brace \"$${\" escape sequence matches braces") {
            ::ShadowPig::Umbra::PreprocessorSequenceTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::Dollar, UTF32Character::Constants::Dollar, UTF32Character::Constants::LeftBrace,
                UTF32Character::Constants::A, 
                UTF32Character::Constants::LeftBrace,UTF32Character::Constants::B, UTF32Character::Constants::RightBrace,
                UTF32Character::Constants::C,
                UTF32Character::Constants::RightBrace,
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfPreprocessorDeclaration,
                UTF32Character::Constants::A,
                UTF32Character::Constants::LeftBrace,
                UTF32Character::Constants::B,
                UTF32Character::Constants::RightBrace,
                UTF32Character::Constants::C,
                UTF32Character::Constants::EndOfPreprocessorDeclaration,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Double Dollar brace \"$${\" escape sequence matches braces (when it contains a string with a brace)") {
            ::ShadowPig::Umbra::PreprocessorSequenceTranslationPhase phase;
            phase.run(UTF32String {
               UTF32Character::Constants::Dollar,  UTF32Character::Constants::Dollar, UTF32Character::Constants::LeftBrace,
                    UTF32Character::Constants::A, 
                    UTF32Character::Constants::LeftBrace,
                        UTF32Character::Constants::StartOfString, UTF32Character::Constants::LeftBrace, UTF32Character::Constants::EndOfString, 
                    UTF32Character::Constants::RightBrace,
                    UTF32Character::Constants::C,
                UTF32Character::Constants::RightBrace,
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfPreprocessorDeclaration,
                UTF32Character::Constants::A,
                UTF32Character::Constants::LeftBrace,
                UTF32Character::Constants::StartOfString,
                UTF32Character::Constants::LeftBrace,
                UTF32Character::Constants::EndOfString,
                UTF32Character::Constants::RightBrace,
                UTF32Character::Constants::C,
                UTF32Character::Constants::EndOfPreprocessorDeclaration,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Replaces Single Dollar brace \"${\" with Preprocessor usage start, and end brace with Preprocessor usage end") {
            ::ShadowPig::Umbra::PreprocessorSequenceTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::Dollar, UTF32Character::Constants::LeftBrace,
                UTF32Character::Constants::RightBrace,
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfPreprocessorUsage,
                UTF32Character::Constants::EndOfPreprocessorUsage,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Replaces Single Dollar brace \"${\" with Preprocessor usage start, and end brace with Preprocessor usage end (containing characters") {
            ::ShadowPig::Umbra::PreprocessorSequenceTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::Dollar, UTF32Character::Constants::LeftBrace,
                UTF32Character::Constants::A, UTF32Character::Constants::B, UTF32Character::Constants::C,
                UTF32Character::Constants::RightBrace,
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfPreprocessorUsage,
                UTF32Character::Constants::A,
                UTF32Character::Constants::B,
                UTF32Character::Constants::C,
                UTF32Character::Constants::EndOfPreprocessorUsage,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Replaces Single Dollar brace \"${\" with Preprocessor usage start, and end brace with Preprocessor usage end (inside string)") {
            ::ShadowPig::Umbra::PreprocessorSequenceTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::StartOfString,
                UTF32Character::Constants::Dollar, UTF32Character::Constants::LeftBrace,
                UTF32Character::Constants::RightBrace,
                UTF32Character::Constants::EndOfString,
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfString,
                UTF32Character::Constants::StartOfPreprocessorUsage,
                UTF32Character::Constants::EndOfPreprocessorUsage,
                UTF32Character::Constants::EndOfString,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Single Dollar brace \"${\" escape sequence matches braces") {
            ::ShadowPig::Umbra::PreprocessorSequenceTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::Dollar, UTF32Character::Constants::LeftBrace,
                UTF32Character::Constants::A, 
                UTF32Character::Constants::LeftBrace,UTF32Character::Constants::B, UTF32Character::Constants::RightBrace,
                UTF32Character::Constants::C,
                UTF32Character::Constants::RightBrace,
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfPreprocessorUsage,
                UTF32Character::Constants::A,
                UTF32Character::Constants::LeftBrace,
                UTF32Character::Constants::B,
                UTF32Character::Constants::RightBrace,
                UTF32Character::Constants::C,
                UTF32Character::Constants::EndOfPreprocessorUsage,
                UTF32Character::Constants::EndOfUnit
            });
        }
    }
}