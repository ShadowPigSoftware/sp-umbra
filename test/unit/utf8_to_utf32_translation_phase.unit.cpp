#include <spunit>
#include <spunit_macros>

#include "translation/utf8_to_utf32_translation_phase.hpp"
#include "test-doubles/fake_file_system.hpp"

spunitModule {
    fixture("UTF-8 to UTF-32 Translation Phase") {
        scenario("Has an accessible End of Unit value") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            expect(::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase::EndOfUnit).to.equal(0xFFFFFFFFu);   //End of Unit
        }

        scenario("Returns a load file error if the file does not exist") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            expect(phase.loadFile("/invalid_file.umb", fakeFileSystem)).to.equal(::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase::LoadFileResult::FILE_NO_EXIST);
        }

        scenario("Maps an empty file to a UTF-32 encoded empty string") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addTextFile("/full/path/test.umb", "");
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            phase.run();
            expect(phase.output().length()).to.equal(1u);
            auto it = phase.output().begin();
            expect(*it).to.equal(::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase::EndOfUnit);   //End of Unit
        }

        scenario("Maps an single character file to a UTF-32 encoded string") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addTextFile("/full/path/test.umb", "a");
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            phase.run();
            expect(phase.output().length()).to.equal(2u);
            auto it = phase.output().begin();
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character::Constants::a);
            ++it;
            expect(*it).to.equal(0xFFFFFFFFu);   //End of Unit
        }

        scenario("Maps an single character file to a UTF-32 encoded string (different value)") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addTextFile("/full/path/test.umb", "P");
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            phase.run();
            expect(phase.output().length()).to.equal(2u);
            auto it = phase.output().begin();
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character::Constants::P);
            ++it;
            expect(*it).to.equal(0xFFFFFFFFu);   //End of Unit
        }

        scenario("Maps an ASCII sequenced character file to a UTF-32 encoded string") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addTextFile("/full/path/test.umb", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            phase.run();
            expect(phase.output().length()).to.equal(26u + 26u + 1u);  
            auto it = phase.output().begin();
            for (uint32_t i = 0; i < 26; ++i)
            {
                expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character('a' + i));
                ++it;
            }

            for (uint32_t i = 0; i < 26; ++i)
            {
                expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character('A' + i));
                ++it;
            }
            expect(*it).to.equal(0xFFFFFFFFu);   //End of Unit
        }

        scenario("Maps a 2-byte UTF8 encoded character file to a UTF-32 encoded string (0x80-0xFF)") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xC2, 0xA3, 0xC3, 0xAF}); //£ï
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            phase.run();
            expect(phase.output().length()).to.equal(3u);  
            auto it = phase.output().begin();
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x000000A3u));
            ++it;
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x000000EFu));
            ++it;
            expect(*it).to.equal(0xFFFFFFFFu);   //End of Unit
        }

         scenario("Maps a 2-byte UTF8 encoded character file to a UTF-32 encoded string (0x80 & 0xFF)") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xC2, 0x80, 0xC3, 0xBF}); //[xxx]ÿ
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            phase.run();
            expect(phase.output().length()).to.equal(3u);  
            auto it = phase.output().begin();
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x00000080u));
            ++it;
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x000000FFu));
            ++it;
            expect(*it).to.equal(0xFFFFFFFFu);   //End of Unit
        }

        scenario("Maps a 2-byte UTF8 encoded character file to a UTF-32 encoded string (0x100-0x7FF)") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;

            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xC4, 0x91, 0xDB, 0xAF}); //đۯ
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            phase.run();
            expect(phase.output().length()).to.equal(3u);  
            auto it = phase.output().begin();
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x00000111u));
            ++it;
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x000006EFu));
            ++it;
            expect(*it).to.equal(0xFFFFFFFFu);   //End of Unit
        }

        scenario("Maps a 2-byte UTF8 encoded character file to a UTF-32 encoded string (0x100 & 0x7FF)") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;

            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xC4, 0x80, 0xDF, 0xBF}); //Ā߿
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            phase.run();
            expect(phase.output().length()).to.equal(3u);  
            auto it = phase.output().begin();
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x00000100u));
            ++it;
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x000007FFu));
            ++it;
            expect(*it).to.equal(0xFFFFFFFFu);   //End of Unit
        }

        scenario("Maps a 3-byte UTF8 encoded character file to a UTF-32 encoded string (0x800-0xFFF)") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xE0, 0xA7, 0xA1, 0xE0, 0xBB, 0x96}); //ৡ໖

            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            phase.run();
            expect(phase.output().length()).to.equal(3u);  
            auto it = phase.output().begin();
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x000009E1u));
            ++it;
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x00000ED6u));
            ++it;
            expect(*it).to.equal(0xFFFFFFFFu);   //End of Unit
        }

         scenario("Maps a 3-byte UTF8 encoded character file to a UTF-32 encoded string (0x800 & 0xFFF)") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xE0, 0xA0, 0x80, 0xE0, 0xBF, 0xBF});
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            phase.run();
            expect(phase.output().length()).to.equal(3u);  
            auto it = phase.output().begin();
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x00000800u));
            ++it;
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x00000FFFu));
            ++it;
            expect(*it).to.equal(0xFFFFFFFFu);   //End of Unit
        }

        scenario("Maps a 3-byte UTF8 encoded character file to a UTF-32 encoded string (0x1000-0xFFFF)") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;

            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xE1, 0x84, 0x91, 0xE7, 0xA6, 0xAB});
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            phase.run();
            expect(phase.output().length()).to.equal(3u);  
            auto it = phase.output().begin();
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x00001111u));
            ++it;
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x000079ABu));
            ++it;
            expect(*it).to.equal(0xFFFFFFFFu);   //End of Unit
        }

        scenario("Maps a 3-byte UTF8 encoded character file to a UTF-32 encoded string (0x1000 & 0xFFFF)") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;

            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xE1, 0x80, 0x80, 0xEF, 0xBF, 0xBF});
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            phase.run();
            expect(phase.output().length()).to.equal(3u);  
            auto it = phase.output().begin();
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x00001000u));
            ++it;
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x0000FFFFu));
            ++it;
            expect(*it).to.equal(0xFFFFFFFFu);   //End of Unit
        }

        scenario("Maps a 4-byte UTF8 encoded character file to a UTF-32 encoded string (0x10000-0x10FFFF)") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;

            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xF0, 0x91, 0x84, 0x91, 0xF3, 0xA1, 0xAA, 0x94});
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            phase.run();
            expect(phase.output().length()).to.equal(3u);  
            auto it = phase.output().begin();
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x00011111u));
            ++it;
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x000E1A94u));
            ++it;
            expect(*it).to.equal(0xFFFFFFFFu);   //End of Unit
        }

        scenario("Maps a 4-byte UTF8 encoded character file to a UTF-32 encoded string (0x10000 & 0x10FFFF)") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;

            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xF0, 0x90, 0x80, 0x80, 0xF4, 0x8F, 0xBF, 0xBF});
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            phase.run();
            expect(phase.output().length()).to.equal(3u);  
            auto it = phase.output().begin();
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x00010000u));
            ++it;
            expect(*it).to.equal(::ShadowPig::Umbra::UTF32Character(0x0010FFFFu));
            ++it;
            expect(*it).to.equal(0xFFFFFFFFu);   //End of Unit
        }

        scenario("Throws an error for a sequence beginning with a continuation byte") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0x82, 0xA3, 0xC3, 0xAF});
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            bool exceptionThrown = false;
            try {
                phase.run();
            } catch (const ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase::InvalidCharacterException& exception) {
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }

        scenario("Throws an error for a sequence beginning with a 0b11111xxx byte") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xF8, 0x32});
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            bool exceptionThrown = false;
            try {
                phase.run();
            } catch (const ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase::InvalidCharacterException& exception) {
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }

        scenario("Throws an error for a 2-byte sequence without a continuation byte") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xC2});
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            bool exceptionThrown = false;
            try {
                phase.run();
            } catch (const ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase::InvalidCharacterException& exception) {
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }

         scenario("Throws an error for a 2-byte sequence with an invalid continuation byte") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xC2, 0x32});
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            bool exceptionThrown = false;
            try {
                phase.run();
            } catch (const ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase::InvalidCharacterException& exception) {
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }

        scenario("Throws an error for a 3-byte sequence without the first continuation byte") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xE1});
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            bool exceptionThrown = false;
            try {
                phase.run();
            } catch (const ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase::InvalidCharacterException& exception) {
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }

         scenario("Throws an error for a 3-byte sequence without the second continuation byte") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xE1, 0x80});
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            bool exceptionThrown = false;
            try {
                phase.run();
            } catch (const ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase::InvalidCharacterException& exception) {
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }

        scenario("Throws an error for a 3-byte sequence with an invalid first continuation byte") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xE1, 0x32, 0x80});
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            bool exceptionThrown = false;
            try {
                phase.run();
            } catch (const ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase::InvalidCharacterException& exception) {
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }

        scenario("Throws an error for a 3-byte sequence with an invalid second continuation byte") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xE1, 0x80, 0x32});
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            bool exceptionThrown = false;
            try {
                phase.run();
            } catch (const ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase::InvalidCharacterException& exception) {
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }

        scenario("Throws an error for a 4-byte sequence without the first continuation byte") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xF1});
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            bool exceptionThrown = false;
            try {
                phase.run();
            } catch (const ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase::InvalidCharacterException& exception) {
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }

        scenario("Throws an error for a 4-byte sequence without the second continuation byte") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xF1, 0x80});
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            bool exceptionThrown = false;
            try {
                phase.run();
            } catch (const ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase::InvalidCharacterException& exception) {
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }

         scenario("Throws an error for a 4-byte sequence without the third continuation byte") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xF1, 0x80, 0x80});
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            bool exceptionThrown = false;
            try {
                phase.run();
            } catch (const ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase::InvalidCharacterException& exception) {
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }

        scenario("Throws an error for a 4-byte sequence with an invalid first continuation byte") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xF1, 0x32, 0x80, 0x80});
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            bool exceptionThrown = false;
            try {
                phase.run();
            } catch (const ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase::InvalidCharacterException& exception) {
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }

        scenario("Throws an error for a 4-byte sequence with an invalid second continuation byte") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xF1, 0x80, 0x32, 0x80});
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            bool exceptionThrown = false;
            try {
                phase.run();
            } catch (const ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase::InvalidCharacterException& exception) {
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }

        scenario("Throws an error for a 4-byte sequence with an invalid third continuation byte") {
            ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase phase;
            ::ShadowPig::Umbra::FakeFileSystem fakeFileSystem;
            fakeFileSystem.addBinaryFile("/full/path/test.umb", {0xF1, 0x80, 0x80, 0x32});
            phase.loadFile("/full/path/test.umb", fakeFileSystem);
            bool exceptionThrown = false;
            try {
                phase.run();
            } catch (const ::ShadowPig::Umbra::Utf8ToUtf32TranslationPhase::InvalidCharacterException& exception) {
                exceptionThrown = true;
            }
            expect(exceptionThrown).to.equal(true);
        }
    }
}