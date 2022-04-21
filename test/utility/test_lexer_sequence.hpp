#pragma once

#include <spunit>
#include <spunit_macros>

#include "translation/lexer/lexer_tokens.hpp"

namespace ShadowPig::Umbra::Test {
    void testLexerSequence(::SPUnit::ScenarioDelegate& delegate, const LexerTokens& actual, std::initializer_list<LexerToken> expected);
}