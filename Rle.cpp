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
                count = 0;
            }
        }
        result.putBack(count);
        result.putBack(input[i]);
    }

    return result;
}

VectorArray<char> RleCompress::decompressImpl(const char* input, size_t size)
{
    VectorArray<char> result;
    for (int i = 0; i < size; i += 2) {
        auto num = input[i];
        while (num) {
            result.putBack(input[i + 1]);
            --num;
        }
    }

    return result;
}

} // namespace string_alg
