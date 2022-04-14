#pragma once

#include "core/utf32_string.hpp"

namespace ShadowPig::Umbra {
    class StringLiteralTranslationPhase {
    public:
        void run(const UTF32String& string);
        const UTF32String& output() const;
    private:
        struct ProcessCharacterOutput {
            bool process;
            UTF32Character character;    
        };
        ProcessCharacterOutput processCharacter(const UTF32Character& character);
        ProcessCharacterOutput processCharacterInsideString(const UTF32Character& character);
        ProcessCharacterOutput processCharacterOutsideString(const UTF32Character& character);
        ProcessCharacterOutput processEscapedCharacter(const UTF32Character& character);
        ProcessCharacterOutput processUnescapedCharacter(const UTF32Character& character);
    private:
        UTF32String _output;
        bool _inString;
        bool _escape;
    };
}
