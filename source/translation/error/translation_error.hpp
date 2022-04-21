#pragma once

#include <stdint.h>
#include <stdexcept>

namespace ShadowPig::Umbra {
    class TranslationError: public std::runtime_error {
    public:
        TranslationError(const std::string& message, uint32_t line, uint32_t column);
        uint32_t line() const;
        uint32_t column() const;
    private:
        uint32_t _line;
        uint32_t _column;
    };
}
