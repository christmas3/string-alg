#pragma once

#include "StringAlg.h"

namespace string_alg {
class Kmp : public find<Kmp>
{
    SizeType findImpl(const char* str, const char* pattern);
    static SizeType findPrefix(const char* str, SizeType strLength, SizeType prefixLength);

    friend struct find;
};
} // namespace string_alg
