#include <spunit>
#include <spunit_macros>

#include "translation/string_literal_translation_phase.hpp"
#include "test-doubles/fake_file_system.hpp"
#include "utility/test_character_sequence.hpp"

using UTF32Character = ::ShadowPig::Umbra::UTF32Character;
using UTF32String = ::ShadowPig::Umbra::UTF32String;

spunitModule {
    fixture("String Literal Translation Phase") {
         scenario("Empty output by default") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {});
         }

        scenario("Replaces Empty string with Start & End") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::EndOfUnit});
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfString,
                UTF32Character::Constants::EndOfString,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Replaces string containing characters with Start & End") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::a, UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::EndOfUnit});
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfString,
                UTF32Character::Constants::a,
                UTF32Character::Constants::EndOfString,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Replaces string containing characters with Start & End (different values)") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::q, UTF32Character::Constants::Z, UTF32Character::Constants::Period, UTF32Character::Constants::h, 
                UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit});
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfString,
                UTF32Character::Constants::q,
                UTF32Character::Constants::Z,
                UTF32Character::Constants::Period,
                UTF32Character::Constants::h,
                UTF32Character::Constants::EndOfString,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Replaces multiple strings containing characters with Start & End") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::a, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::D, UTF32Character::Constants::DoubleQuote,
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfString,
                UTF32Character::Constants::a,
                UTF32Character::Constants::EndOfString,
                UTF32Character::Constants::StartOfString,
                UTF32Character::Constants::D,
                UTF32Character::Constants::EndOfString,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Replaces an escaped \'a\' with the bell character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::a, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfString,
                UTF32Character::Constants::EscapedBell,
                UTF32Character::Constants::EndOfString,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Replaces an escaped \'b\' with the backspace character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::b, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfString,
                UTF32Character::Constants::EscapedBackspace,
                UTF32Character::Constants::EndOfString,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Replaces an escaped \'e\' with the escape character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::e, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfString,
                UTF32Character::Constants::EscapedEscape,
                UTF32Character::Constants::EndOfString,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Replaces an escaped \'f\' with the form-feed character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::f, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfString,
                UTF32Character::Constants::EscapedFormFeed,
                UTF32Character::Constants::EndOfString,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Replaces an escaped \'n\' with the line-feed character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::n, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfString,
                UTF32Character::Constants::EscapedLineFeed,
                UTF32Character::Constants::EndOfString,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Replaces an escaped \'r\' with the carriage return character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::r, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfString,
                UTF32Character::Constants::EscapedCarriageReturn,
                UTF32Character::Constants::EndOfString,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Replaces an escaped \'t\' with the tab character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::t, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfString,
                UTF32Character::Constants::EscapedHorizontalTab,
                UTF32Character::Constants::EndOfString,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Replaces an escaped \'v\' with the vertical tab character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::v, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfString,
                UTF32Character::Constants::EscapedVerticalTab,
                UTF32Character::Constants::EndOfString,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Replaces an escaped \'\\\' with the backslash character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::Backslash, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfString,
                UTF32Character::Constants::EscapedBackslash,
                UTF32Character::Constants::EndOfString,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Replaces an escaped \"\"\" with the double quote character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfString,
                UTF32Character::Constants::EscapedDoubleQuote,
                UTF32Character::Constants::EndOfString,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Replaces an escaped \"$\" with the escaped dollar character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::Dollar, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            ::ShadowPig::Umbra::Test::testCharacterSequence(*this, phase.output(), {
                UTF32Character::Constants::StartOfString,
                UTF32Character::Constants::EscapedDollar,
                UTF32Character::Constants::EndOfString,
                UTF32Character::Constants::EndOfUnit
            });
        }

        scenario("Throws an error for an invalid escaped character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
             bool exceptionThrown = false;
            try {
                phase.run(UTF32String {
                    UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::d, UTF32Character::Constants::DoubleQuote, 
                    UTF32Character::Constants::EndOfUnit
                });
            } catch (const ::ShadowPig::Umbra::StringLiteralTranslationPhase::InvalidEscapeCharacterException& exception) {
                expect(exception.character()).to.equal(UTF32Character::Constants::d);
                expect(exception.line()).to.equal(1u);
                expect(exception.column()).to.equal(3u);
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }

        scenario("Throws an error for an invalid escaped character (different value)") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
             bool exceptionThrown = false;
            try {
                phase.run(UTF32String {
                    UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::Z, UTF32Character::Constants::DoubleQuote, 
                    UTF32Character::Constants::EndOfUnit
                });
            } catch (const ::ShadowPig::Umbra::StringLiteralTranslationPhase::InvalidEscapeCharacterException& exception) {
                expect(exception.character()).to.equal(UTF32Character::Constants::Z);
                expect(exception.line()).to.equal(1u);
                expect(exception.column()).to.equal(3u);
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }

        scenario("Throws an error for an invalid escaped character (different position)") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
             bool exceptionThrown = false;
            try {
                phase.run(UTF32String {
                    UTF32Character::Constants::LineFeed, UTF32Character::Constants::LineFeed,
                    UTF32Character::Constants::A, UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::Z, UTF32Character::Constants::DoubleQuote, 
                    UTF32Character::Constants::EndOfUnit
                });
            } catch (const ::ShadowPig::Umbra::StringLiteralTranslationPhase::InvalidEscapeCharacterException& exception) {
                expect(exception.character()).to.equal(UTF32Character::Constants::Z);
                expect(exception.line()).to.equal(3u);
                expect(exception.column()).to.equal(4u);
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }

        scenario("Throws an error for an incomplete string") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
             bool exceptionThrown = false;
            try {
                phase.run(UTF32String {
                    UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Z, UTF32Character::Constants::EndOfUnit
                });
            } catch (const ::ShadowPig::Umbra::StringLiteralTranslationPhase::IncompleteStringException& exception) {
                expect(exception.line()).to.equal(1u);
                expect(exception.column()).to.equal(3u);
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }

        scenario("Throws an error for an incomplete string (after backslash)") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
             bool exceptionThrown = false;
            try {
                phase.run(UTF32String {
                    UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::EndOfUnit
                });
            } catch (const ::ShadowPig::Umbra::StringLiteralTranslationPhase::IncompleteStringException& exception) {
                expect(exception.line()).to.equal(1u);
                expect(exception.column()).to.equal(3u);
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }

        scenario("Throws an error for an incomplete string (double quote after backslash)") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
             bool exceptionThrown = false;
            try {
                phase.run(UTF32String {
                    UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::EndOfUnit
                });
            } catch (const ::ShadowPig::Umbra::StringLiteralTranslationPhase::IncompleteStringException& exception) {
                expect(exception.line()).to.equal(1u);
                expect(exception.column()).to.equal(4u);
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }
    }
}