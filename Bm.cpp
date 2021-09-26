#include "Bm.h"

namespace string_alg {

SizeType Bm::operator()(const char* str, const char* pattern)
{
    size_t patternLength = getLength(pattern);
    fillShift(pattern, patternLength);
    if (patternLength > 1) {
        fillSuffix(pattern, patternLength);
    }
    int t = 0;
    int last = patternLength - 1;
    size_t textLength = getLength(str);
    while (t < textLength - last) {
        int p = last;
        while (p >= 0 && str[t + p] == pattern[p]) {
            --p;
        }

        if (p == -1) {
            return t;
        }

        if (last - p < 2) {
            t += shift_[str[t + last]];
        }
        else {
            t += suffix_[last - p];
        }
    }

    return kNpos;
}

void Bm::fillShift(const char* pattern, size_t length)
{
    for (int i = 0; i < 128; ++i) {
        shift_[i] = length;
    }
    for (int i = 0; i < length - 1; ++i) {
        shift_[pattern[i]] = length - i - 1;
    }
}

size_t Bm::getLength(const char* pattern)
{
    size_t length = 0;
    while (*pattern++)
        ++length;
    return length;
}

void Bm::fillSuffix(const char* pattern, size_t length)
{
    delete[] suffix_;
    suffix_ = new int[length + 1];
    suffix_[0] = suffix_[1] = length;

    int lastPrefix = length;
    for (int i = (int)length - 2; i >= 0; --i) {
        if (isPrefix(pattern, length, i)) {
            lastPrefix = i;
        }
        suffix_[length - i] = lastPrefix;
    }
    for (int i = 1; i < length - 2; ++i) {
        auto size = suffixLength(pattern, length, i);
        if (size) {
            suffix_[size] = length - 1 - i;
        }
    }
}

bool Bm::isPrefix(const char* pattern, size_t length, size_t p)
{
    for (int i = p, j = 0; i < length; ++i, ++j) {
        if (pattern[j] != pattern[i]) {
            return false;
        }
    }
    return true;
}

size_t Bm::suffixLength(const char* pattern, size_t length, size_t p)
{
    size_t result = 0;
    int i = p;
    int j = length - 1;
    while (i >= 0 && pattern[i] == pattern[j]) {
        ++result;
        --i;
        --j;
    }
    return result;
}

} // namespace string_alg
