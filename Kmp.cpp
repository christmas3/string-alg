#include "Kmp.h"

#include <iostream>

namespace string_alg {

static const char kDelimiter = '@';

SizeType Kmp::findImpl(const char* str, const char* pattern)
{
    auto patternLength = getLength(pattern);
    auto strLength = getLength(str);
    char* strCon = new char[strLength + patternLength + 2];
    char* strConPtr = strCon;
    const char* patternPtr = pattern;
    while (*patternPtr) {
        *strConPtr++ = *patternPtr++;
    }
    *strConPtr++ = kDelimiter;
    while (*strConPtr++ = *str++)
        ;

    auto result = findPrefix(strCon, strLength + patternLength + 1, patternLength);
    delete[] strCon;
    return result;
}

SizeType Kmp::findPrefix(const char* str, SizeType strLength, SizeType prefixLength)
{
    int* pi = new int[strLength];
    pi[0] = 0;
    SizeType result = kNpos;

    for (SizeType i = 1; i < strLength; ++i) {
        int j = pi[i - 1];
        while ((j > 0) && (str[i] != str[j]))
            j = pi[j - 1];

        if (str[i] == str[j])
            ++j;
        if (j == prefixLength) {
            result = i - prefixLength - prefixLength;
            break;
        }
        pi[i] = j;
    }

    delete[] pi;
    return result;
}

} // namespace string_alg
