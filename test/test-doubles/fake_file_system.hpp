#pragma once

#include "filesystem/filesystem.hpp"
#include "fake_file.hpp"
#include <stdint.h>
#include <string>
#include <vector>
#include <map>

namespace ShadowPig::Umbra {
    class FakeFileSystem: public FileSystem {
    public:
        bool exists(const std::string& filename) const override;
        File open(const std::string& filename, File::Mode mode) const override;
    public:
        // Fake filesystem methods
        void addTextFile(const std::string& filename, const std::string& contents);  
        void addBinaryFile(const std::string& filename, std::initializer_list<uint8_t> contents);  
    private:
        using FileMap = std::map<std::string, FakeFile::Contents>;
        FileMap _fileMap;
    };
}