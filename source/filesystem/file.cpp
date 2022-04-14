#include "file.hpp"
#include "file_implementation.hpp"

namespace ShadowPig::Umbra {
    File::File():
        _implementation(nullptr)
    {}

    File::File(Private::FileImplementation* implementation):
        _implementation(implementation) 
    {}

    File::File(File&& file):
        _implementation(file._implementation)
    {
        file._implementation = nullptr;
    }

    File& File::operator=(File&& file) {
        if (this != &file) {
            delete _implementation;
            _implementation = file._implementation;
            file._implementation = nullptr;
        }
        return *this;
    }
        
    File::~File() {
        delete _implementation;
    }

    File::OpenResult File::open(std::string& filename, Mode mode) {
        if (_implementation) {
            return _implementation->open(filename, mode) ? File::OpenResult::SUCCESS : File::OpenResult::FILE_NO_EXIST;
        }
        return File::OpenResult::INVALID_HANDLE;
    }

    bool File::isValid() const {
        return (_implementation == nullptr) ? false : _implementation->isValid();
    }

    bool File::readByte(uint8_t& byte) {
        return (_implementation == nullptr) ? false : _implementation->readByte(byte);
    }
}