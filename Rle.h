#pragma once

#include "StringAlg.h"

namespace string_alg {

class RleCompress : public archive<RleCompress>
{
private:
    VectorArray<char> compressImpl(const char*, size_t);
    VectorArray<char> decompressImpl(const char*, size_t);

    friend struct archive;
};

class RleAdvancedCompress : public archive<RleAdvancedCompress>
{
private:
    VectorArray<char> compressImpl(const char*, size_t);
    VectorArray<char> decompressImpl(const char*, size_t);

    friend struct archive;
};

} // namespace string_alg
