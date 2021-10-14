#pragma once

#include "StringAlg.h"

namespace string_alg {
class Bm : public find<Bm>
{
public:
    Bm()
        : suffix_(nullptr)
    {
    }
    ~Bm() { delete[] suffix_; }

private:
    SizeType findImpl(const char* str, const char* pattern);

    void fillShift(const char* pattern, size_t length);
    void fillSuffix(const char* pattern, size_t length);

    static bool isPrefix(const char* pattern, size_t length, size_t p);
    static size_t suffixLength(const char* pattern, size_t length, size_t p);

    char shift_[128];
    int* suffix_;

    friend struct find;
};

} // namespace string_alg
