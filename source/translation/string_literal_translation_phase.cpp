#include "string_literal_translation_phase.hpp"
#include "core/unused.hpp"

#include <map>

namespace ShadowPig::Umbra {
    namespace {
        using EscapeCharacterMap = std::map<UTF32Character, UTF32Character>;
        EscapeCharacterMap escapeCharacterMap = {
            {UTF32Character::Constants::a, UTF32Character::Constants::EscapedBell},
            {UTF32Character::Constants::b, UTF32Character::Constants::EscapedBackspace},
            {UTF32Character::Constants::e, UTF32Character::Constants::EscapedEscape},
            {UTF32Character::Constants::f, UTF32Character::Constants::EscapedFormFeed},
            {UTF32Character::Constants::n, UTF32Character::Constants::EscapedLineFeed},
            {UTF32Character::Constants::r, UTF32Character::Constants::EscapedCarriageReturn},
            {UTF32Character::Constants::t, UTF32Character::Constants::EscapedHorizontalTab},
            {UTF32Character::Constants::v, UTF32Character::Constants::EscapedVerticalTab},
            {UTF32Character::Constants::Backslash, UTF32Character::Constants::EscapedBackslash},
            {UTF32Character::Constants::DoubleQuote, UTF32Character::Constants::EscapedDoubleQuote},
            {UTF32Character::Constants::Dollar, UTF32Character::Constants::EscapedDollar}
        };
    }

     StringLiteralTranslationPhase::InvalidEscapeCharacterException::InvalidEscapeCharacterException(const UTF32Character& character, uint32_t line, uint32_t column):
        TranslationError("Invalid escape character", line, column),
        _character(character)
    {}

    const UTF32Character& StringLiteralTranslationPhase::InvalidEscapeCharacterException::character() const {
        return _character;
    }

    StringLiteralTranslationPhase::IncompleteStringException::IncompleteStringException(uint32_t line, uint32_t column):
        TranslationError("Incomplete string", line, column)
    {}

    void StringLiteralTranslationPhase::run(const UTF32String& string) {
        _inString = false;
        _escape = false;
        UTF32String::PositionIterator iterator(string);
        while (iterator.isValid()) {
            auto result = processCharacter(iterator);
            if (result.process) {
                _output += result.character;
            }
            ++iterator;
        }
    }
        
    const UTF32String& StringLiteralTranslationPhase::output() const {
        return _output;
    }

    StringLiteralTranslationPhase::ProcessCharacterOutput StringLiteralTranslationPhase::processCharacter(const UTF32String::PositionIterator& iterator) {
        if (_inString) {
            return processCharacterInsideString(iterator);
        }
        return processCharacterOutsideString(iterator);
    }

    StringLiteralTranslationPhase::ProcessCharacterOutput StringLiteralTranslationPhase::processCharacterInsideString(const UTF32String::PositionIterator& iterator) {
        if (_escape) {
            return processEscapedCharacter(iterator);
        }
        return processUnescapedCharacter(iterator);
    }

    StringLiteralTranslationPhase::ProcessCharacterOutput StringLiteralTranslationPhase::processCharacterOutsideString(const UTF32String::PositionIterator& iterator) {
        const UTF32Character& character = *iterator;
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

    StringLiteralTranslationPhase::ProcessCharacterOutput StringLiteralTranslationPhase::processEscapedCharacter(const UTF32String::PositionIterator& iterator) {
        _escape = false;
        const UTF32Character& character = *iterator;
        auto it = escapeCharacterMap.find(character);
        if (it != escapeCharacterMap.end())
        {
            return ProcessCharacterOutput {
                .process = true, 
                .character = it->second
            };  
        }
        else if (character == UTF32Character::Constants::EndOfUnit) {
            throw IncompleteStringException(iterator.line(), iterator.column());
        }
        throw InvalidEscapeCharacterException(character, iterator.line(), iterator.column());
    }

    StringLiteralTranslationPhase::ProcessCharacterOutput StringLiteralTranslationPhase::processUnescapedCharacter(const UTF32String::PositionIterator& iterator) {
        const UTF32Character& character = *iterator;
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
                .character = UTF32Character::Constants::EndOfString
            }; 
        }
        else if (character == UTF32Character::Constants::EndOfUnit) {
            throw IncompleteStringException(iterator.line(), iterator.column());
        }
        return ProcessCharacterOutput {
            .process = true, 
            .character = character
        };
    }
}
