#include "translation_error.hpp"

namespace ShadowPig::Umbra {
    TranslationError::TranslationError(const std::string& message, uint32_t line, uint32_t column):
        runtime_error(message),
        _line(line),
        _column(column)
    {}
    
    uint32_t TranslationError::line() const {
        return _line;
    }

    uint32_t TranslationError::column() const {
        return _column;
    }
}
