#pragma once

#include "file.hpp"
namespace ShadowPig::Umbra {
    class FileSystem {
    public:
        virtual ~FileSystem() = default;

        virtual bool exists(const std::string& filename) const = 0;
        virtual File open(const std::string& filename, File::Mode mode) const = 0;
    protected:
        File makeFile(Private::FileImplementation* implementation) const;
    };
}