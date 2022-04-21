#include "test_lexer_sequence.hpp"

namespace ShadowPig::Umbra::Test {
    void testLexerSequence(::SPUnit::ScenarioDelegate& delegate, const LexerTokens& actual, std::initializer_list<LexerToken> expected) {
        delegate.expect(actual.size()).to.equal(expected.size());
        auto it = actual.begin();
        for (LexerToken token: expected) {
            delegate.expect(*it).to.equal(token);
            ++it;
        }
    }
}