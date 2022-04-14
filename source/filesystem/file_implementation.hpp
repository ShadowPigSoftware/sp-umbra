#pragma once

#include "file_mode.hpp"
#include <string>

namespace ShadowPig::Umbra {
    namespace Private {
        class FileImplementation {
        public:
            virtual ~FileImplementation() = default;
            virtual bool open(std::string& filename, FileMode mode) = 0;
            virtual bool isValid() const= 0;
            virtual bool readByte(uint8_t& byte) = 0;
        };
    }
}