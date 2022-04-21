#pragma once

#include "core/utf32_string.hpp"
#include "filesystem/filesystem.hpp"
#include <string>


namespace ShadowPig::Umbra {
    class Utf8ToUtf32TranslationPhase {
    public:
        enum class LoadFileResult {
            SUCCESS,
            FILE_NO_EXIST
        };
        LoadFileResult loadFile(const std::string& filename, FileSystem& filesystem);

        void run();
        const UTF32String& output() const;

        static constexpr UTF32Character EndOfUnit = UTF32Character::Constants::EndOfUnit;

        class InvalidCharacterException: public std::runtime_error {
        public:
            InvalidCharacterException();
        };
    private:
        void process1ByteUTF8Character(uint8_t firstByte);
        void process2ByteUTF8Character(uint8_t firstByte);
        void process3ByteUTF8Character(uint8_t firstByte);
        void process4ByteUTF8Character(uint8_t firstByte);

        void validateContinuationByte(uint8_t byte);
    private:
        File _file;
        UTF32String _output;
    };

    using UTUTP = Utf8ToUtf32TranslationPhase;
}
