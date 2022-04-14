#include "utf8_to_utf32_translation_phase.hpp"
#include "core/unused.hpp"

namespace ShadowPig::Umbra {

    Utf8ToUtf32TranslationPhase::InvalidCharacterException::InvalidCharacterException():
        runtime_error("Invalid UTF8 character") 
    {}

    Utf8ToUtf32TranslationPhase::LoadFileResult Utf8ToUtf32TranslationPhase::loadFile(const std::string& filename, FileSystem& filesystem) {
        if (filesystem.exists(filename)) {
            _file = filesystem.open(filename, FileMode::Read);
            if (_file.isValid())
            {
                return Utf8ToUtf32TranslationPhase::LoadFileResult::SUCCESS;
            }
        }
        
        return Utf8ToUtf32TranslationPhase::LoadFileResult::FILE_NO_EXIST;
    }

    void Utf8ToUtf32TranslationPhase::run() {
        uint8_t byte= 0;
        while (_file.readByte(byte)) {
            if ((byte & 0x80) == 0x00)
            {
                //ASCII Range
                process1ByteUTF8Character(byte);
                
            } 
            else if ((byte & 0xC0) == 0x80)
            {
                //this is an error, UTF8 reserves this space for continuation characters
                throw InvalidCharacterException();
            }
            else if ((byte & 0xE0) == 0xC0)
            {
                process2ByteUTF8Character(byte);
            }

            else if ((byte & 0xF0) == 0xE0)
            {
                process3ByteUTF8Character(byte);
            }
            else if ((byte & 0xF8) == 0xF0)
            {
                process4ByteUTF8Character(byte);
            }
            else {
                //this is an error, UTF8 reserves this space for future use
                //this is the range 0b11111xxx
                throw InvalidCharacterException();
            }
        }
        _output.push_back(UTF32Character {0xFFFFFFFF});
    }

    const UTF32String& Utf8ToUtf32TranslationPhase::output() const {
        return _output;
    }

    void Utf8ToUtf32TranslationPhase::process1ByteUTF8Character(uint8_t firstByte) {
        _output.push_back(UTF32Character {firstByte});
    }

    void Utf8ToUtf32TranslationPhase::process2ByteUTF8Character(uint8_t firstByte) {
        uint32_t value = 0;
        value |= static_cast<uint32_t>(firstByte & 0x1F) << 6;
        uint8_t secondByte = 0;
        if (!_file.readByte(secondByte)) {
            throw InvalidCharacterException();
        }
        validateContinuationByte(secondByte);
        value |= static_cast<uint32_t>(secondByte & 0x3F) << 0;
        _output.push_back(UTF32Character {value});
    }

    void Utf8ToUtf32TranslationPhase::process3ByteUTF8Character(uint8_t firstByte) {
        uint32_t value = 0;
        value |= static_cast<uint32_t>(firstByte & 0x0F) << 12;
        uint8_t secondByte = 0;
        if (!_file.readByte(secondByte)) {
            throw InvalidCharacterException();
        }
        validateContinuationByte(secondByte);
        value |= static_cast<uint32_t>(secondByte & 0x3F) << 6;
        uint8_t thirdByte = 0;
        if (!_file.readByte(thirdByte)) {
            throw InvalidCharacterException();
        }
        validateContinuationByte(thirdByte);
        value |= static_cast<uint32_t>(thirdByte & 0x3F) << 0;
        _output.push_back(UTF32Character {value});
    }

    void Utf8ToUtf32TranslationPhase::process4ByteUTF8Character(uint8_t firstByte) {
        uint32_t value = 0;
        value |= static_cast<uint32_t>(firstByte & 0x07) << 18;
        uint8_t secondByte = 0;
        if (!_file.readByte(secondByte)) {
            throw InvalidCharacterException();
        }
        validateContinuationByte(secondByte);
        value |= static_cast<uint32_t>(secondByte & 0x3F) << 12;
        uint8_t thirdByte = 0;
        if (!_file.readByte(thirdByte)) {
            throw InvalidCharacterException();
        }
        validateContinuationByte(thirdByte);
        value |= static_cast<uint32_t>(thirdByte & 0x3F) << 6;
        uint8_t forthByte = 0;
        if (!_file.readByte(forthByte)) {
            throw InvalidCharacterException();
        }
        validateContinuationByte(forthByte);
        value |= static_cast<uint32_t>(forthByte & 0x3F) << 0;
        _output.push_back(UTF32Character {value});
    }

    void Utf8ToUtf32TranslationPhase::validateContinuationByte(uint8_t byte) {
        if ((byte & 0xC0) != 0x80) {
            throw InvalidCharacterException();
        }
    }
}