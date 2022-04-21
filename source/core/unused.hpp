#pragma once

namespace ShadowPig::Umbra::Internal {
    template <class ...Args> constexpr void unused(Args&&...) {}
}