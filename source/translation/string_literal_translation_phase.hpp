#pragma once

#include "core/utf32_string.hpp"
#include "error/translation_error.hpp"

namespace ShadowPig::Umbra {
    class StringLiteralTranslationPhase {
    public:
        void run(const UTF32String& string);
        const UTF32String& output() const;

        class InvalidEscapeCharacterException: public TranslationError {
        public:
            InvalidEscapeCharacterException(const UTF32Character& character, uint32_t line, uint32_t column);
            const UTF32Character& character() const;
        private:
            UTF32Character _character;
        };

        class IncompleteStringException: public TranslationError {
        public:
            IncompleteStringException(uint32_t line, uint32_t column);
        };
    private:
        struct ProcessCharacterOutput {
            bool process;
            UTF32Character character;    
        };
        ProcessCharacterOutput processCharacter(const UTF32Character& character, uint32_t line, uint32_t column);
        ProcessCharacterOutput processCharacterInsideString(const UTF32Character& character, uint32_t line, uint32_t column);
        ProcessCharacterOutput processCharacterOutsideString(const UTF32Character& character, uint32_t line, uint32_t column);
        ProcessCharacterOutput processEscapedCharacter(const UTF32Character& character, uint32_t line, uint32_t column);
        ProcessCharacterOutput processUnescapedCharacter(const UTF32Character& character, uint32_t line, uint32_t column);
    private:
        UTF32String _output;
        bool _inString;
        bool _escape;
    };

    using SLTP = StringLiteralTranslationPhase;
}
