#include <spunit>
#include <spunit_macros>

#include "translation/preprocessor_lexer/preprocessor_lexer_translation_phase.hpp"
#include "test-doubles/fake_file_system.hpp"

using LexerToken = ::ShadowPig::Umbra::LexerToken;
using LexerTokens = ::ShadowPig::Umbra::LexerTokens;
using UTF32Character = ::ShadowPig::Umbra::UTF32Character;
using UTF32String = ::ShadowPig::Umbra::UTF32String;

namespace {
    void testSymbolToken(::SPUnit::ScenarioDelegate& delegate, const UTF32Character& symbol, LexerToken::Type type) {
        ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
        phase.run(UTF32String {
            UTF32Character::Constants::StartOfPreprocessorDeclaration,
            symbol,
            UTF32Character::Constants::EndOfPreprocessorDeclaration,
            UTF32Character::Constants::EndOfUnit
        });
        delegate.expect(phase.output().size()).to.equal(1u);
        auto itBlock = phase.output().begin();
        delegate.expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
        const LexerTokens& tokens = itBlock->tokens();
        delegate.expect(tokens.size()).to.equal(1u);
        auto it = tokens.begin();
        delegate.expect(it->type()).to.equal(type);
        delegate.expect(it->lexeme()).to.equal(UTF32String {symbol});
        delegate.expect(it->line()).to.equal(1u);
        delegate.expect(it->column()).to.equal(4u);
    }
}

spunitModule {
    fixture("Preprocessor Lexer Translation Phase") {
        scenario("Empty output by default") {
            ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
            expect(phase.output().size()).to.equal(0u);
        }

        fixture("Alpha Tokens") {
            scenario("Replaces Preprocessor Declaration Alpha Token (single character)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::a,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::Alpha);
                expect(it->lexeme()).to.equal(UTF32String {UTF32Character::Constants::a});
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Alpha Token (different single character)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::P,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::Alpha);
                expect(it->lexeme()).to.equal(UTF32String {UTF32Character::Constants::P});
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Alpha Token (multiple characters)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::a, UTF32Character::Constants::b, UTF32Character::Constants::c, UTF32Character::Constants::d,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::Alpha);
                expect(it->lexeme()).to.equal(UTF32String {
                    UTF32Character::Constants::a, UTF32Character::Constants::b, UTF32Character::Constants::c, UTF32Character::Constants::d
                });
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Alpha Token (different multiple characters)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::F, UTF32Character::Constants::l, UTF32Character::Constants::A, UTF32Character::Constants::m, UTF32Character::Constants::E,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::Alpha);
                expect(it->lexeme()).to.equal(UTF32String {
                    UTF32Character::Constants::F, UTF32Character::Constants::l, UTF32Character::Constants::A, UTF32Character::Constants::m, UTF32Character::Constants::E
                });
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Alpha Token (beginning with underscore)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::Underscore, UTF32Character::Constants::l, UTF32Character::Constants::A, UTF32Character::Constants::m, UTF32Character::Constants::E,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::Alpha);
                expect(it->lexeme()).to.equal(UTF32String {
                    UTF32Character::Constants::Underscore, UTF32Character::Constants::l, UTF32Character::Constants::A, UTF32Character::Constants::m, UTF32Character::Constants::E
                });
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Alpha Token (containing underscore)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::Underscore, UTF32Character::Constants::l, UTF32Character::Constants::Underscore, UTF32Character::Constants::m, UTF32Character::Constants::Underscore,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::Alpha);
                expect(it->lexeme()).to.equal(UTF32String {
                    UTF32Character::Constants::Underscore, UTF32Character::Constants::l, UTF32Character::Constants::Underscore, UTF32Character::Constants::m, UTF32Character::Constants::Underscore
                });
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Alpha Token (alpha followed by numbers)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::A, UTF32Character::Constants::One, UTF32Character::Constants::Three, UTF32Character::Constants::Five, UTF32Character::Constants::Eight,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::Alpha);
                expect(it->lexeme()).to.equal(UTF32String {
                    UTF32Character::Constants::A, UTF32Character::Constants::One, UTF32Character::Constants::Three, UTF32Character::Constants::Five, UTF32Character::Constants::Eight
                });
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Alpha Token (underscore followed by numbers)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::Underscore, UTF32Character::Constants::One, UTF32Character::Constants::Three, UTF32Character::Constants::Five, UTF32Character::Constants::Eight,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::Alpha);
                expect(it->lexeme()).to.equal(UTF32String {
                    UTF32Character::Constants::Underscore, UTF32Character::Constants::One, UTF32Character::Constants::Three, UTF32Character::Constants::Five, UTF32Character::Constants::Eight
                });
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Alpha Token (terminates on whitespace)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::Underscore, UTF32Character::Constants::One, UTF32Character::Constants::Space,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(2u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::Alpha);
                expect(it->lexeme()).to.equal(UTF32String {
                    UTF32Character::Constants::Underscore, UTF32Character::Constants::One
                });
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Alpha Token (terminates on symbol)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::Underscore, UTF32Character::Constants::One, UTF32Character::Constants::Colon,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(2u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::Alpha);
                expect(it->lexeme()).to.equal(UTF32String {
                    UTF32Character::Constants::Underscore, UTF32Character::Constants::One
                });
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }
        }

        fixture("Whitespace Tokens") {
            scenario("Replaces Preprocessor Declaration Whitespace Token (space)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::Space,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::Whitespace);
                expect(it->lexeme()).to.equal(UTF32String {UTF32Character::Constants::Space});
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Whitespace Token (tab)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::HorizontalTab,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::Whitespace);
                expect(it->lexeme()).to.equal(UTF32String {UTF32Character::Constants::HorizontalTab});
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Whitespace Token (vertical tab)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::VerticalTab,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::Whitespace);
                expect(it->lexeme()).to.equal(UTF32String {UTF32Character::Constants::VerticalTab});
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Whitespace Token (form feed)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::FormFeed,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::Whitespace);
                expect(it->lexeme()).to.equal(UTF32String {UTF32Character::Constants::FormFeed});
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Whitespace Token (line feed)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::LineFeed,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::Whitespace);
                expect(it->lexeme()).to.equal(UTF32String {UTF32Character::Constants::LineFeed});
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Whitespace Token (carriage return)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::CarriageReturn,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::Whitespace);
                expect(it->lexeme()).to.equal(UTF32String {UTF32Character::Constants::CarriageReturn});
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration Whitespace Token (multiple)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::Space, UTF32Character::Constants::Space, UTF32Character::Constants::Space,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::Whitespace);
                expect(it->lexeme()).to.equal(UTF32String {UTF32Character::Constants::Space, UTF32Character::Constants::Space, UTF32Character::Constants::Space});
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }
        }

        fixture("Symbol Tokens") {
            scenario("Replaces Preprocessor Declaration Symbol Token ( ! )") {
                testSymbolToken(*this, UTF32Character::Constants::ExclamationMark, LexerToken::Type::PreprocessorDeclaration::Symbol::ExclamationMark);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( \" )") {
                testSymbolToken(*this, UTF32Character::Constants::DoubleQuote, LexerToken::Type::PreprocessorDeclaration::Symbol::DoubleQuote);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( # )") {
                testSymbolToken(*this, UTF32Character::Constants::Hash, LexerToken::Type::PreprocessorDeclaration::Symbol::Hash);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( $ )") {
                testSymbolToken(*this, UTF32Character::Constants::Dollar, LexerToken::Type::PreprocessorDeclaration::Symbol::Dollar);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( % )") {
                testSymbolToken(*this, UTF32Character::Constants::Percent, LexerToken::Type::PreprocessorDeclaration::Symbol::Percent);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( & )") {
                testSymbolToken(*this, UTF32Character::Constants::Ampersand, LexerToken::Type::PreprocessorDeclaration::Symbol::Ampersand);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( \' )") {
                testSymbolToken(*this, UTF32Character::Constants::SingleQuote, LexerToken::Type::PreprocessorDeclaration::Symbol::SingleQuote);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( ( )") {
                testSymbolToken(*this, UTF32Character::Constants::LeftParenthesis, LexerToken::Type::PreprocessorDeclaration::Symbol::LeftParenthesis);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( ) )") {
                testSymbolToken(*this, UTF32Character::Constants::RightParenthesis, LexerToken::Type::PreprocessorDeclaration::Symbol::RightParenthesis);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( * )") {
                testSymbolToken(*this, UTF32Character::Constants::Asterisk, LexerToken::Type::PreprocessorDeclaration::Symbol::Asterisk);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( + )") {
                testSymbolToken(*this, UTF32Character::Constants::Plus, LexerToken::Type::PreprocessorDeclaration::Symbol::Plus);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( , )") {
                testSymbolToken(*this, UTF32Character::Constants::Comma, LexerToken::Type::PreprocessorDeclaration::Symbol::Comma);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( - )") {
                testSymbolToken(*this, UTF32Character::Constants::Minus, LexerToken::Type::PreprocessorDeclaration::Symbol::Minus);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( . )") {
                testSymbolToken(*this, UTF32Character::Constants::Period, LexerToken::Type::PreprocessorDeclaration::Symbol::Period);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( / )") {
                testSymbolToken(*this, UTF32Character::Constants::Slash, LexerToken::Type::PreprocessorDeclaration::Symbol::Slash);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( : )") {
                testSymbolToken(*this, UTF32Character::Constants::Colon, LexerToken::Type::PreprocessorDeclaration::Symbol::Colon);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( ; )") {
                testSymbolToken(*this, UTF32Character::Constants::Semicolon, LexerToken::Type::PreprocessorDeclaration::Symbol::Semicolon);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( < )") {
                testSymbolToken(*this, UTF32Character::Constants::LessThan, LexerToken::Type::PreprocessorDeclaration::Symbol::LessThan);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( = )") {
                testSymbolToken(*this, UTF32Character::Constants::Equality, LexerToken::Type::PreprocessorDeclaration::Symbol::Equality);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( > )") {
                testSymbolToken(*this, UTF32Character::Constants::GreaterThan, LexerToken::Type::PreprocessorDeclaration::Symbol::GreaterThan);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( ? )") {
                testSymbolToken(*this, UTF32Character::Constants::QuestionMark, LexerToken::Type::PreprocessorDeclaration::Symbol::QuestionMark);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( [ )") {
                testSymbolToken(*this, UTF32Character::Constants::LeftBracket, LexerToken::Type::PreprocessorDeclaration::Symbol::LeftBracket);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( \\ )") {
                testSymbolToken(*this, UTF32Character::Constants::Backslash, LexerToken::Type::PreprocessorDeclaration::Symbol::Backslash);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( ] )") {
                testSymbolToken(*this, UTF32Character::Constants::RightBracket, LexerToken::Type::PreprocessorDeclaration::Symbol::RightBracket);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( ^ )") {
                testSymbolToken(*this, UTF32Character::Constants::Caret, LexerToken::Type::PreprocessorDeclaration::Symbol::Caret);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( ` )") {
                testSymbolToken(*this, UTF32Character::Constants::Backtick, LexerToken::Type::PreprocessorDeclaration::Symbol::Backtick);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( { )") {
                testSymbolToken(*this, UTF32Character::Constants::LeftBrace, LexerToken::Type::PreprocessorDeclaration::Symbol::LeftBrace);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( | )") {
                testSymbolToken(*this, UTF32Character::Constants::Pipe, LexerToken::Type::PreprocessorDeclaration::Symbol::Pipe);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( } )") {
                testSymbolToken(*this, UTF32Character::Constants::RightBrace, LexerToken::Type::PreprocessorDeclaration::Symbol::RightBrace);
            }

            scenario("Replaces Preprocessor Declaration Symbol Token ( ~ )") {
                testSymbolToken(*this, UTF32Character::Constants::Tilde, LexerToken::Type::PreprocessorDeclaration::Symbol::Tilde);
            }
        }

        fixture("String Tokens") {
            scenario("Replaces Preprocessor Declaration String Token ") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::StartOfString,
                    UTF32Character::Constants::A,
                    UTF32Character::Constants::EndOfString,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::String);
                expect(it->lexeme()).to.equal(UTF32String {
                    UTF32Character::Constants::StartOfString, 
                    UTF32Character::Constants::A, 
                    UTF32Character::Constants::EndOfString
                });
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration String Token (different values)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::StartOfString,
                    UTF32Character::Constants::L,
                    UTF32Character::Constants::Colon,
                    UTF32Character::Constants::P,
                    UTF32Character::Constants::QuestionMark,
                    UTF32Character::Constants::EndOfString,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::String);
                expect(it->lexeme()).to.equal(UTF32String {
                    UTF32Character::Constants::StartOfString, 
                    UTF32Character::Constants::L, UTF32Character::Constants::Colon, UTF32Character::Constants::P, UTF32Character::Constants::QuestionMark,
                    UTF32Character::Constants::EndOfString
                });
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }

            scenario("Replaces Preprocessor Declaration String Token (escaped characters)") {
                ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
                phase.run(UTF32String {
                    UTF32Character::Constants::StartOfPreprocessorDeclaration,
                    UTF32Character::Constants::StartOfString,
                    UTF32Character::Constants::EscapedDollar,
                    UTF32Character::Constants::EscapedDoubleQuote,
                    UTF32Character::Constants::EscapedBackspace,
                    UTF32Character::Constants::EscapedCarriageReturn,
                    UTF32Character::Constants::EndOfString,
                    UTF32Character::Constants::EndOfPreprocessorDeclaration,
                    UTF32Character::Constants::EndOfUnit
                });
                expect(phase.output().size()).to.equal(1u);
                auto itBlock = phase.output().begin();
                expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
                const LexerTokens& tokens = itBlock->tokens();
                expect(tokens.size()).to.equal(1u);
                auto it = tokens.begin();
                expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::String);
                expect(it->lexeme()).to.equal(UTF32String {
                    UTF32Character::Constants::StartOfString, 
                    UTF32Character::Constants::EscapedDollar, UTF32Character::Constants::EscapedDoubleQuote, UTF32Character::Constants::EscapedBackspace, UTF32Character::Constants::EscapedCarriageReturn,
                    UTF32Character::Constants::EndOfString
                });
                expect(it->line()).to.equal(1u);
                expect(it->column()).to.equal(4u);
            }
        }

        fixture("Numeric Tokens") {
            // scenario("Replaces Preprocessor Declaration Numeric Token (zero)") {
            //     ::ShadowPig::Umbra::PreprocessorLexerTranslationPhase phase;
            //     phase.run(UTF32String {
            //         UTF32Character::Constants::StartOfPreprocessorDeclaration,
            //         UTF32Character::Constants::Zero,
            //         UTF32Character::Constants::EndOfPreprocessorDeclaration,
            //         UTF32Character::Constants::EndOfUnit
            //     });
            //     expect(phase.output().size()).to.equal(1u);
            //     auto itBlock = phase.output().begin();
            //     expect(itBlock->type()).to.equal(::ShadowPig::Umbra::PLTP::Block::Type::PreprocessorDeclaration);
            //     const LexerTokens& tokens = itBlock->tokens();
            //     expect(tokens.size()).to.equal(1u);
            //     auto it = tokens.begin();
            //     expect(it->type()).to.equal(LexerToken::Type::PreprocessorDeclaration::Numeric::Zero);
            //     expect(it->lexeme()).to.equal(UTF32String {UTF32Character::Constants::Zero});
            //     expect(it->line()).to.equal(1u);
            //     expect(it->column()).to.equal(4u);
            // }
        }
    }
}