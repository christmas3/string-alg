#include <gtest/gtest.h>

#include "../Rle.h"
#include "../StringAlg.h"

template<typename T>
void testArchiveString(string_alg::archive<T>& arch, const char* input, size_t inputSize, const char* result, size_t resultSize)
{
    auto compressData = arch.compress(input, inputSize);
    EXPECT_TRUE(string_alg::isStringEqual(compressData.data(), compressData.size(), result, resultSize));
    auto decompressData = arch.decompress(result, resultSize);
    EXPECT_TRUE(string_alg::isStringEqual(decompressData.data(), decompressData.size(), input, inputSize));
}

template<typename T>
void testArchiveFile(const char* input, string_alg::archive<T>& arch, const char* resultSuffix)
{
    auto length = string_alg::getLength(input);
    char* outFile = string_alg::copyWithPrefix(input, length, ".tmp", sizeof(".tmp"));

    EXPECT_TRUE(string_alg::compressFile(input, outFile, arch));

    //compress
    VectorArray<char> outFileData;
    EXPECT_TRUE(string_alg::readFile(outFile, outFileData));

    auto* compressResultFile = string_alg::copyWithPrefix(input, length, resultSuffix, string_alg::getLength(resultSuffix));
    VectorArray<char> compressResultData;
    EXPECT_TRUE(string_alg::readFile(compressResultFile, compressResultData));
    EXPECT_TRUE(string_alg::isStringEqual(outFileData.data(), outFileData.size(), compressResultData.data(), compressResultData.size()));

    //decompress
    EXPECT_TRUE(string_alg::decompressFile(outFile, outFile, arch));
    EXPECT_TRUE(string_alg::readFile(outFile, outFileData));
    EXPECT_TRUE(string_alg::readFile(input, compressResultData));
    EXPECT_TRUE(string_alg::isStringEqual(outFileData.data(), outFileData.size(), compressResultData.data(), compressResultData.size()));

    std::remove(outFile);
    delete[] outFile;
    delete[] compressResultFile;
}

TEST(ArchiveTestSuit, RleTest)
{
    string_alg::RleCompress rle;
    char result[31] = { 9,   '#', 4,   '.', 1,   '#', 1,   '.', 3,   '#', 1,   '.', 1,   '#', 1,
                        '.', 1,   '#', 1,   '.', 2,   '#', 2,   '.', 1,   '#', 3,   '.', 9,   '#' };
    const char inputArr[] = "#########....#.###.#.#.##..#...#########";

    testArchiveString(rle, inputArr, sizeof(inputArr) - 1, result, 30);

    std::string input(1000, 'a');
    result[0] = result[2] = result[4] = 255;
    result[1] = result[3] = result[5] = result[7] = 'a';
    result[6] = 235;
    testArchiveString(rle, input.c_str(), 1000, result, 8);
}

TEST(ArchiveTestSuit, RleFileTest)
{
    string_alg::RleCompress rle;

    for (const auto* input : { "../../test/test_files/file2" }) {
        testArchiveFile(input, rle, ".rle");
    }
}

//TEST(ArchiveTestSuit, RleAdvancedTest)
//{
//    EXPECT_EQ(rle("#########....#.###.#.#.##..#...#########"), "9#4.-2#.3#-5.#.#.2#2.-1#3.9#");
//}

TEST(ArchiveTestSuit, toStringTest)
{
    VectorArray<char> buf;
    string_alg::toString(127, buf);
    buf.putBack('\0');

    EXPECT_FALSE(strcmp(buf.data(), "127")) << " buf: " << buf.data();
}
