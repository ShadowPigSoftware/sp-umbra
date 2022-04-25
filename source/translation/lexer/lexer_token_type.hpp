#pragma once
#include <stdint.h>
#include <iostream>

namespace ShadowPig::Umbra {
    enum class LexerTokenType: uint32_t {
        //Preprocessor
        NonPreprocessorSequence = 0,
        PreprocessorDeclarationAlpha = 1,
        PreprocessorDeclarationWhitespace = 2,
        PreprocessorDeclarationExclamationMark = 3,
        PreprocessorDeclarationDoubleQuote = 4,
        PreprocessorDeclarationHash = 5,
        PreprocessorDeclarationDollar = 6,
        PreprocessorDeclarationPercent = 7,
        PreprocessorDeclarationAmpersand = 8,
        PreprocessorDeclarationSingleQuote = 9,
        PreprocessorDeclarationLeftParenthesis = 10,
        PreprocessorDeclarationRightParenthesis = 11,
        PreprocessorDeclarationAsterisk = 12,
        PreprocessorDeclarationPlus = 13,
        PreprocessorDeclarationComma = 14,
        PreprocessorDeclarationMinus = 15,
        PreprocessorDeclarationPeriod = 16,
        PreprocessorDeclarationSlash = 17,
        PreprocessorDeclarationColon = 18,
        PreprocessorDeclarationSemicolon = 19,
        PreprocessorDeclarationLessThan = 20,
        PreprocessorDeclarationEquality = 21,
        PreprocessorDeclarationGreaterThan = 22,
        PreprocessorDeclarationQuestionMark = 23,
        PreprocessorDeclarationLeftBracket = 24,
        PreprocessorDeclarationBackslash = 25,
        PreprocessorDeclarationRightBracket = 26,
        PreprocessorDeclarationCaret = 27,
        PreprocessorDeclarationBacktick = 28,
        PreprocessorDeclarationLeftBrace = 29,
        PreprocessorDeclarationPipe = 30,
        PreprocessorDeclarationRightBrace = 31,
        PreprocessorDeclarationTilde = 32,

        //Invalid
        Invalid = 0xFFFFFFFF
    };
}

std::ostream& operator << (std::ostream& stream, ShadowPig::Umbra::LexerTokenType type);