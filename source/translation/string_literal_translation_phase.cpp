#include "string_literal_translation_phase.hpp"
#include "core/unused.hpp"

#include <map>

namespace ShadowPig::Umbra {
    namespace {
        using EscapeCharacterMap = std::map<UTF32Character, UTF32Character>;
        EscapeCharacterMap escapeCharacterMap = {
            {UTF32Character::Constants::a, UTF32Character::Constants::Bell},
            {UTF32Character::Constants::b, UTF32Character::Constants::Backspace},
            {UTF32Character::Constants::e, UTF32Character::Constants::Escape},
            {UTF32Character::Constants::f, UTF32Character::Constants::FormFeed},
            {UTF32Character::Constants::n, UTF32Character::Constants::LineFeed},
            {UTF32Character::Constants::r, UTF32Character::Constants::CarriageReturn},
            {UTF32Character::Constants::t, UTF32Character::Constants::HorizontalTab},
            {UTF32Character::Constants::v, UTF32Character::Constants::VerticalTab},
            {UTF32Character::Constants::Backslash, UTF32Character::Constants::Backslash},
            {UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::DoubleQuote},
            {UTF32Character::Constants::Dollar, UTF32Character::Constants::EscapedDollar}
        };
    }

     StringLiteralTranslationPhase::InvalidEscapeCharacterException::InvalidEscapeCharacterException(const UTF32Character& character):
        runtime_error("Invalid escape character"),
        _character(character)
    {}

    const UTF32Character& StringLiteralTranslationPhase::InvalidEscapeCharacterException::character() const {
        return _character;
    }

    StringLiteralTranslationPhase::IncompleteStringException::IncompleteStringException():
        runtime_error("Incomplete string")
    {}

    void StringLiteralTranslationPhase::run(const UTF32String& string) {
        _inString = false;
        _escape = false;
        for (auto character: string) {
            auto result = processCharacter(character);
            if (result.process) {
                _output += result.character;
            }
        }
    }
        
    const UTF32String& StringLiteralTranslationPhase::output() const {
        return _output;
    }

    StringLiteralTranslationPhase::ProcessCharacterOutput StringLiteralTranslationPhase::processCharacter(const UTF32Character& character) {
        if (_inString) {
            return processCharacterInsideString(character);
        }
        return processCharacterOutsideString(character);
    }

    StringLiteralTranslationPhase::ProcessCharacterOutput StringLiteralTranslationPhase::processCharacterInsideString(const UTF32Character& character) {
        if (_escape) {
            return processEscapedCharacter(character);
        }
        return processUnescapedCharacter(character);
    }

    StringLiteralTranslationPhase::ProcessCharacterOutput StringLiteralTranslationPhase::processCharacterOutsideString(const UTF32Character& character) {
        if (character == UTF32Character::Constants::DoubleQuote) {
            _inString = true;
            return ProcessCharacterOutput {
                .process = true, 
                .character = UTF32Character::Constants::StartOfString
            };
        }
        return ProcessCharacterOutput {
            .process = true, 
            .character = character
        };
    }

    StringLiteralTranslationPhase::ProcessCharacterOutput StringLiteralTranslationPhase::processEscapedCharacter(const UTF32Character& character) {
        _escape = false;
        auto it = escapeCharacterMap.find(character);
        if (it != escapeCharacterMap.end())
        {
            return ProcessCharacterOutput {
                .process = true, 
                .character = it->second
            };  
        }
        else if (character == UTF32Character::Constants::EndOfUnit) {
            throw IncompleteStringException();
        }
        throw InvalidEscapeCharacterException {character};
    }

    StringLiteralTranslationPhase::ProcessCharacterOutput StringLiteralTranslationPhase::processUnescapedCharacter(const UTF32Character& character) {
        if (character == UTF32Character::Constants::Backslash) {
            _escape = true;
            return ProcessCharacterOutput {
                .process = false, 
                .character = character //Don't care, this wont be used
            };
        }
        else if (character == UTF32Character::Constants::DoubleQuote) {
            _inString = false;
            return ProcessCharacterOutput {
                .process = true, 
                .character = UTF32Character::Constants::EndOfString //Don't care, this wont be used
            }; 
        }
        else if (character == UTF32Character::Constants::EndOfUnit) {
            throw IncompleteStringException();
        }
        return ProcessCharacterOutput {
            .process = true, 
            .character = character
        };
    }
}
