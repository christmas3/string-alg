#include "Rle.h"

namespace string_alg {

VectorArray<char> RleCompress::compressImpl(const char* input, size_t size)
{
    VectorArray<char> result(size);

    for (int i = 0, j = 1; i < size; i = j, ++j) {
        unsigned char count = 1;
        while (j < size && input[i] == input[j]) {
            ++count;
            ++j;
            if (count == 255) {
                result.putBack(count);
                result.putBack(input[i]);
                i = j;
                ++j;
                count = 1;
            }
        }
        result.putBack(count);
        result.putBack(input[i]);
    }

    return result;
}

VectorArray<char> RleCompress::decompressImpl(const char* input, size_t size)
{
    VectorArray<char> result(size);
    for (int i = 0; i < size; i += 2) {
        auto num = input[i];
        while (num) {
            result.putBack(input[i + 1]);
            --num;
        }
    }

    return result;
}

VectorArray<char> RleAdvancedCompress::compressImpl(const char* input, size_t size)
{
    VectorArray<char> result(size);

    size_t index = 0;
    for (int i = 0, j = 1; i < size; i = j, ++j) {
        char count = 1;
        while (j < size && input[i] == input[j]) {
            ++count;
            ++j;
            if (count == 127) {
                result.putBack(count);
                result.putBack(input[i]);
                i = j;
                ++j;
                count = 1;
                index = 0;
            }
        }
        if (count > 2) {
            result.putBack(count);
            result.putBack(input[i]);
            index = 0;
        }
        else {
            if (!index) {
                result.putBack(-count);
                index = result.size() - 1;
            }
            else {
                result[index] -= count;
            }
            result.putBack(input[i]);
            if (count == 2) {
                result.putBack(input[i]);
            }
            while (j + 1 < size && input[j] != input[j + 1]) {
                result[index] -= 1;
                result.putBack(input[j]);
                ++j;
                if (result[index] == -128) {
                    index = 0;
                    break;
                }
            }
        }
    }

    return result;
}

//VectorArray<char> RleAdvancedCompress::decompressImpl(const char* input, size_t size)
//{
//    VectorArray<char> result(size);
//
//    size_t i = 0;
//    while (i < size) {
//        if (input[i] == '-') {
//            int count = input[++i];
//            while (count--) {
//                result.putBack(input[++i]);
//            }
//        }
//    }
//}

} // namespace string_alg
