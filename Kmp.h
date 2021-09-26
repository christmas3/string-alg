#pragma once

#include "StringAlg.h"

namespace string_alg {
class Kmp
{
public:
    SizeType operator()(const char* str, const char* pattern);

private:
    static SizeType findPrefix(const char* str, SizeType strLength, SizeType prefixLength);
};
} // namespace string_alg
