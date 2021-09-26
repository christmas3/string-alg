#pragma once

#include <cstddef>
namespace string_alg {

using SizeType = size_t;
const SizeType kNpos = -1;

template<typename T>
struct find : public T
{
    // return pos of pattern in str or kNpos
    SizeType operator()(const char* str, const char* pattern) { return derived()->operator()(str, pattern); }

private:
    T* derived() { return static_cast<T*>(this); }
};

inline SizeType getLength(const char* pattern)
{
    size_t length = 0;
    const char* p = pattern;
    while (*p++) {
        ++length;
    }

    return length;
}

} // namespace string_alg
