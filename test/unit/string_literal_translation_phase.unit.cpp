#include <spunit>
#include <spunit_macros>

#include "translation/string_literal_translation_phase.hpp"
#include "test-doubles/fake_file_system.hpp"

using UTF32Character = ::ShadowPig::Umbra::UTF32Character;
using UTF32String = ::ShadowPig::Umbra::UTF32String;

spunitModule {
    fixture("String Literal Translation Phase") {
         scenario("Empty output by default") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            expect(phase.output().length()).to.equal(0u);
         }

        scenario("Replaces Empty string with Start & End") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::EndOfUnit});
            expect(phase.output().length()).to.equal(3u);
            auto it = phase.output().begin();
            expect(*it).to.equal(UTF32Character::Constants::StartOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfUnit);
        }

        scenario("Replaces string containing characters with Start & End") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::a, UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::EndOfUnit});
            expect(phase.output().length()).to.equal(4u);
            auto it = phase.output().begin();
            expect(*it).to.equal(UTF32Character::Constants::StartOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::a);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfUnit);
        }

        scenario("Replaces string containing characters with Start & End (different values)") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::q, UTF32Character::Constants::Z, UTF32Character::Constants::Period, UTF32Character::Constants::h, 
                UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit});
            expect(phase.output().length()).to.equal(7u);
            auto it = phase.output().begin();
            expect(*it).to.equal(UTF32Character::Constants::StartOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::q);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::Z);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::Period);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::h);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfUnit);
        }

        scenario("Replaces multiple strings containing characters with Start & End") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::a, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::D, UTF32Character::Constants::DoubleQuote,
                UTF32Character::Constants::EndOfUnit
            });
            expect(phase.output().length()).to.equal(7u);
            auto it = phase.output().begin();
            expect(*it).to.equal(UTF32Character::Constants::StartOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::a);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::StartOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::D);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfUnit);
        }

        scenario("Replaces an escaped \'a\' with the bell character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::a, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            expect(phase.output().length()).to.equal(4u);
            auto it = phase.output().begin();
            expect(*it).to.equal(UTF32Character::Constants::StartOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::Bell);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfUnit);
        }

        scenario("Replaces an escaped \'b\' with the backspace character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::b, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            expect(phase.output().length()).to.equal(4u);
            auto it = phase.output().begin();
            expect(*it).to.equal(UTF32Character::Constants::StartOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::Backspace);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfUnit);
        }

        scenario("Replaces an escaped \'e\' with the escape character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::e, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            expect(phase.output().length()).to.equal(4u);
            auto it = phase.output().begin();
            expect(*it).to.equal(UTF32Character::Constants::StartOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::Escape);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfUnit);
        }

        scenario("Replaces an escaped \'f\' with the form-feed character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::f, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            expect(phase.output().length()).to.equal(4u);
            auto it = phase.output().begin();
            expect(*it).to.equal(UTF32Character::Constants::StartOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::FormFeed);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfUnit);
        }

        scenario("Replaces an escaped \'n\' with the line-feed character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::n, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            expect(phase.output().length()).to.equal(4u);
            auto it = phase.output().begin();
            expect(*it).to.equal(UTF32Character::Constants::StartOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::LineFeed);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfUnit);
        }

        scenario("Replaces an escaped \'r\' with the carriage return character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::r, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            expect(phase.output().length()).to.equal(4u);
            auto it = phase.output().begin();
            expect(*it).to.equal(UTF32Character::Constants::StartOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::CarriageReturn);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfUnit);
        }

        scenario("Replaces an escaped \'t\' with the tab character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::t, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            expect(phase.output().length()).to.equal(4u);
            auto it = phase.output().begin();
            expect(*it).to.equal(UTF32Character::Constants::StartOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::HorizontalTab);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfUnit);
        }

        scenario("Replaces an escaped \'v\' with the vertical tab character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::v, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            expect(phase.output().length()).to.equal(4u);
            auto it = phase.output().begin();
            expect(*it).to.equal(UTF32Character::Constants::StartOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::VerticalTab);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfUnit);
        }

        scenario("Replaces an escaped \'\\\' with the backslash character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::Backslash, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            expect(phase.output().length()).to.equal(4u);
            auto it = phase.output().begin();
            expect(*it).to.equal(UTF32Character::Constants::StartOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::Backslash);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfUnit);
        }

        scenario("Replaces an escaped \"\"\" with the double quote character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            expect(phase.output().length()).to.equal(4u);
            auto it = phase.output().begin();
            expect(*it).to.equal(UTF32Character::Constants::StartOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::DoubleQuote);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfUnit);
        }

        scenario("Replaces an escaped \"$\" with the dollar character") {
            ::ShadowPig::Umbra::StringLiteralTranslationPhase phase;
            phase.run(UTF32String {
                UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::Backslash, UTF32Character::Constants::Dollar, UTF32Character::Constants::DoubleQuote, 
                UTF32Character::Constants::EndOfUnit
            });
            expect(phase.output().length()).to.equal(4u);
            auto it = phase.output().begin();
            expect(*it).to.equal(UTF32Character::Constants::StartOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::Dollar);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfString);
            ++it;
            expect(*it).to.equal(UTF32Character::Constants::EndOfUnit);
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
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }
    }
}