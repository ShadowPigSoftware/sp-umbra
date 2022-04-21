#pragma once

#include <spunit>
#include <spunit_macros>

#include "core/utf32_string.hpp"

namespace ShadowPig::Umbra::Test {
    void testCharacterSequence(::SPUnit::ScenarioDelegate& delegate, const UTF32String& actual, std::initializer_list<UTF32Character> expected);
}