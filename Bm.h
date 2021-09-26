#pragma once

#include "StringAlg.h"

namespace string_alg {
class Bm
{
public:
    SizeType operator()(const char* str, const char* pattern);

    Bm()
        : suffix_(nullptr)
    {
    }
    ~Bm() { delete[] suffix_; }

private:
    void fillShift(const char* pattern, size_t length);
    void fillSuffix(const char* pattern, size_t length);

    static size_t getLength(const char* pattern);
    static bool isPrefix(const char* pattern, size_t length, size_t p);
    static size_t suffixLength(const char* pattern, size_t length, size_t p);

    char shift_[128];
    int* suffix_;
};

} // namespace string_alg
