#include "fake_file.hpp"
#include "core/unused.hpp"

namespace ShadowPig::Umbra {
    FakeFile::FakeFile(const Contents& contents):
        _contents(contents),
        _contentsIterator(_contents.begin())
    {}
    
    bool FakeFile::open(std::string& filename, FileMode mode)
    {
        Internal::unused(filename, mode);
        
        return true;
    }

    bool FakeFile::isValid() const {
        return true;
    }

    bool FakeFile::readByte(uint8_t& byte) {
        if (_contentsIterator == _contents.end()) {
            return false;
        }
        byte = *_contentsIterator;
        ++_contentsIterator;
        return true;
    }
}