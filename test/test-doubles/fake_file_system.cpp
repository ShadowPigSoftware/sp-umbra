#include "fake_file_system.hpp"
#include "fake_file.hpp"
#include "core/unused.hpp"

namespace ShadowPig::Umbra {

    bool FakeFileSystem::exists(const std::string& filename) const {
        return _fileMap.find(filename) != _fileMap.end();
    }

    File FakeFileSystem::open(const std::string& filename, File::Mode mode) const {
        Internal::unused(mode);
        auto it = _fileMap.find(filename);
        if (it == _fileMap.end()) {
            return File();
        }

        return makeFile(new FakeFile(it->second));
    }

    void FakeFileSystem::addTextFile(const std::string& filename, const std::string& contents) {
        FakeFile::Contents fileContents(contents.begin(), contents.end());
        _fileMap.insert(FileMap::value_type {filename, fileContents});
    }

    void FakeFileSystem::addBinaryFile(const std::string& filename, std::initializer_list<uint8_t> contents) {
        FakeFile::Contents fileContents(contents.begin(), contents.end());
        _fileMap.insert(FileMap::value_type {filename, fileContents});
    }
}