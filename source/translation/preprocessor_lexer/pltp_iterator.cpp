#include "pltp_iterator.hpp"

namespace ShadowPig::Umbra {
    PLTP_Iterator::PreprocessorLexerTranslationPhaseIterator(const UTF32String& string):
        _it(string.begin()),
        _end(string.end()),
        _line(1),
        _column(1)
    {}

    bool PLTP_Iterator::isValid() const {
        return _it != _end;
    }
    
    const UTF32Character& PLTP_Iterator::operator* () const {
        return *_it;
    }
        
    uint32_t PLTP_Iterator::line() const
    {
        return _line;
    }
        
    uint32_t PLTP_Iterator::column() const
    {
        return _column;
    }

    PLTP_Iterator& PLTP_Iterator::operator++()
    {
        if (_it != _end) {
            if (*_it == UTF32Character::Constants::LineFeed) {
                ++_line;
                _column = 1;
            }
            else {
                _column+=_it->width();
            }
            ++_it;
        }
        return *this;
    }

}
