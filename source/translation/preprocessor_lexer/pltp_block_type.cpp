#include "pltp_block_type.hpp"

std::ostream& operator << (std::ostream& stream, ::ShadowPig::Umbra::PLTP_BlockType type)
{
    switch (type) {
    case ::ShadowPig::Umbra::PLTP_BlockType::NonPreprocessor:
        stream << "NonPreprocessor";
        break;
    case ::ShadowPig::Umbra::PLTP_BlockType::PreprocessorImplementation:
        stream << "PreprocessorImplementation";
        break;
    case ::ShadowPig::Umbra::PLTP_BlockType::PreprocessorUsage:
        stream << "PreprocessorUsage";
        break;
    }
    return stream;
}