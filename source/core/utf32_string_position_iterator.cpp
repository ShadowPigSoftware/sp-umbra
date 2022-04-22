#include "utf32_string_position_iterator.hpp"

namespace ShadowPig::Umbra {
    UTF32StringPositionIterator::UTF32StringPositionIterator(const std::basic_string<UTF32Character>& string):
        _it(string.begin()),
        _end(string.end()),
        _line(1),
        _column(1)
    {}

    bool UTF32StringPositionIterator::isValid() const {
        return _it != _end;
    }
    
    const UTF32Character& UTF32StringPositionIterator::operator* () const {
        return *_it;
    }
        
    uint32_t UTF32StringPositionIterator::line() const
    {
        return _line;
    }
        
    uint32_t UTF32StringPositionIterator::column() const
    {
        return _column;
    }

    UTF32StringPositionIterator& UTF32StringPositionIterator::operator++()
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
