#pragma once

#include "file_mode.hpp"
#include <string>

namespace ShadowPig::Umbra {
    namespace Private {
        class FileImplementation;
    }

    class File {
        friend class FileSystem;
    public:
        using Mode = FileMode;
        File();
        File(const File& file) = delete; //Do not allow copying of files
        File(File&& file);

        File& operator=(const File& file); //Do not allow copying of files
        File& operator=(File&& file);
        ~File();

        enum class OpenResult {
            SUCCESS,
            FILE_NO_EXIST,
            INVALID_HANDLE
        };
        OpenResult open(std::string& filename, Mode mode);

        bool isValid() const;

        bool readByte(uint8_t& byte);
    protected:
        File(Private::FileImplementation* implementation);
    protected:
        Private::FileImplementation* _implementation;
    };
}