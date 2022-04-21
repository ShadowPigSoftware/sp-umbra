#pragma once

#include "core/utf32_string.hpp"

namespace ShadowPig::Umbra {
    class PreprocessorLexerTranslationPhaseIterator {
    public:
        PreprocessorLexerTranslationPhaseIterator(const UTF32String& string);

        bool isValid() const;
        const UTF32Character& operator* () const;
        uint32_t line() const;
        uint32_t column() const;

        PreprocessorLexerTranslationPhaseIterator& operator++();
    private:
        UTF32String::const_iterator _it;
        UTF32String::const_iterator _end;
        uint32_t _line;
        uint32_t _column;
    };

    using PLTP_Iterator = PreprocessorLexerTranslationPhaseIterator;
}
