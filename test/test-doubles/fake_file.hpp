#pragma once

#include "filesystem/file_implementation.hpp"

#include <vector>

namespace ShadowPig::Umbra {
    class FakeFile: public Private::FileImplementation {
    public:
        using Contents = std::vector<uint8_t>;
        FakeFile(const Contents& contents);
        bool open(std::string& filename, FileMode mode) override;
        bool isValid() const override;
        bool readByte(uint8_t& byte) override;
    private:
        Contents _contents;
        Contents::const_iterator _contentsIterator;
    };
}