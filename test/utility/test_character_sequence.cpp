#include "test_character_sequence.hpp"

namespace ShadowPig::Umbra::Test {
    void testCharacterSequence(::SPUnit::ScenarioDelegate& delegate, const UTF32String& actual, std::initializer_list<UTF32Character> expected) {
        delegate.expect(actual.length()).to.equal(expected.size());
        auto it = actual.begin();
        for (UTF32Character character: expected) {
            delegate.expect(*it).to.equal(character);
            ++it;
        }
    }
}