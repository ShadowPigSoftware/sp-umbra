#include "pltp_block_type.hpp"

std::ostream& operator << (std::ostream& stream, ::ShadowPig::Umbra::PLTP_BlockType type)
{
    switch (type) {
    case ::ShadowPig::Umbra::PLTP_BlockType::NonPreprocessor:
        stream << "NonPreprocessor";
        break;
    case ::ShadowPig::Umbra::PLTP_BlockType::PreprocessorDeclaration:
        stream << "PreprocessorDeclaration";
        break;
    case ::ShadowPig::Umbra::PLTP_BlockType::PreprocessorUsage:
        stream << "PreprocessorUsage";
        break;
    }
    return stream;
}