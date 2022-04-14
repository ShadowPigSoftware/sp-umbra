#include "filesystem.hpp"

namespace ShadowPig::Umbra {
    File FileSystem::makeFile(Private::FileImplementation* implementation) const {
        return File(implementation);
    }
}