#pragma once

#include "VectorArray.h"

#include <cstddef>
#include <functional>
#include <iostream>

namespace string_alg {

using SizeType = size_t;
const SizeType kNpos = -1;

template<typename T>
struct find
{
    // return pos of pattern in str or kNpos
    SizeType operator()(const char* str, const char* pattern) { return derived()->findImpl(str, pattern); }

private:
    T* derived() { return static_cast<T*>(this); }
    SizeType findImpl(const char* str, const char* pattern) { return kNpos; }
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

template<typename T>
struct archive
{
    VectorArray<char> compress(const char* str, size_t size) { return derived()->compressImpl(str, size); }
    VectorArray<char> decompress(const char* str, size_t size) { return derived()->decompressImpl(str, size); }

private:
    T* derived() { return static_cast<T*>(this); }
};

inline bool readFile(const char* in, VectorArray<char>& buf)
{
    if (auto fp = std::fopen(in, "rb")) {
        std::fseek(fp, 0L, SEEK_END);
        auto fileSize = std::ftell(fp);
        std::fseek(fp, 0L, SEEK_SET);
        VectorArray<char> bufTmp(fileSize + 1);
        int c;
        while ((c = std::fgetc(fp)) != EOF) {
            bufTmp.putBack(c);
        }
        std::fclose(fp);

        buf = std::move(bufTmp);

        return true;
    }

    std::perror("file opening error for read");
    return false;
}

template<typename T>
inline bool compressFile(const char* in, const char* out, archive<T>& archiver)
{
    return archiverFileImpl(in, out, std::bind(&archive<T>::compress, archiver, std::placeholders::_1, std::placeholders::_2));
}

template<typename T>
inline bool decompressFile(const char* in, const char* out, archive<T>& archiver)
{
    return archiverFileImpl(in, out, std::bind(&archive<T>::decompress, archiver, std::placeholders::_1, std::placeholders::_2));
}

inline bool archiverFileImpl(const char* in, const char* out, const std::function<VectorArray<char>(const char*, size_t)>& operation)
{
    VectorArray<char> buf;
    if (readFile(in, buf)) {
        if (auto fpWrite = std::fopen(out, "wb")) {
            auto compress = operation(buf.data(), buf.size());
            auto result = std::fwrite(compress.data(), sizeof(char), compress.size(), fpWrite);
            if (result != compress.size()) {
                std::fclose(fpWrite);
                std::perror("error while writing in file");
                return false;
            }
            std::fclose(fpWrite);
            return true;
        }
        std::perror("file opening error for write");
        return false;
    }
    return false;
}

inline void toString(unsigned char number, VectorArray<char>& vec)
{
    size_t size = vec.size();
    while (number) {
        vec.put((number % 10) + '0', size);
        number /= 10;
    }
}

inline bool isStringEqual(const char* str1, size_t str1Size, const char* str2, size_t str2Size)
{
    if (str1Size != str2Size) {
        return false;
    }

    int cur = 0;
    while (cur < str1Size && str1[cur] == str2[cur]) {
        ++cur;
    }

    return cur == str1Size;
}

inline void copyString(const char* src, char* dst)
{
    const char* srcPtr = src;
    char* dstPtr = dst;
    while (*dst++ = *src++) {}
}

inline char* copyWithPrefix(const char* src, size_t srcSize, const char* suffix, size_t suffixLength)
{
    char* dst = new char[srcSize + suffixLength + 1];
    string_alg::copyString(src, dst);
    for (int i = 0; i < suffixLength; ++i) {
        dst[srcSize + i] = suffix[i];
    }
    dst[srcSize + suffixLength] = '\0';

    return dst;
}

} // namespace string_alg
