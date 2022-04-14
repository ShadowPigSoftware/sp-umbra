#pragma once

#include "file_implementation.hpp"
#include "file_mode.hpp"
#include <cstdio>
#include <string>

namespace ShadowPig::Umbra {
    namespace Private {
        class StandardFileImplementation: public FileImplementation {
        public:
            StandardFileImplementation(const std::string& filename, FileMode mode);
            bool open(std::string& filename, FileMode mode) override;
        private:
            FILE* _file;
        };
    }
}