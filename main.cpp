#include <cstring>
#include <iostream>

#include "Kmp.h"
#include "Rle.h"
#include "StringAlg.h"

enum OperationType
{
    Compress,
    Decompress
};

template<typename T>
bool doOperation(string_alg::archive<T>& arch, OperationType type, const char* filename)
{
    char* outFile = nullptr;
    bool result = false;
    const char suffix[] = ".arch";
    if (type == Compress) {
        outFile = string_alg::copyWithPrefix(filename, string_alg::getLength(filename), suffix, sizeof(suffix));
        result = string_alg::compressFile(filename, outFile, arch);
    }
    else {
        string_alg::Kmp kmp;
        auto pos = kmp(filename, suffix);
        if (pos == string_alg::kNpos) {
            std::cerr << "invalid archive file format. Must be .arch" << std::endl;
            result = false;
        }
        else {
            outFile = new char[pos + 1];
            string_alg::copyString(filename, outFile, pos);
            outFile[pos] = '\0';
            std::cerr << "outFile: " << outFile << std::endl;
            result = string_alg::decompressFile(filename, outFile, arch);
        }
    }

    delete[] outFile;
    return result;
}

int main(int argc, char** argv)
{
    if (argc == 1) {
        auto progName = basename(argv[0]);
        std::cerr << "Usage:" << std::endl
                  << progName << " [-1|-2] filename\t\t\t - for compress filename into filename.arch -1 - rle alg; -2 - rle advanced alg"
                  << std::endl
                  << progName << " [-1|-2] -d filename.arch\t - for decompress filename.arch into filename";
        return 1;
    }

    enum
    {
        Rle,
        RleAdvanced
    } algType = Rle;

    OperationType operationType = Compress;

    char* filename = nullptr;

    if (argc == 2) {
        std::cerr << "compress with rle alg" << std::endl;
        filename = argv[1];
    }
    else if (argc == 3) {
        filename = argv[2];
        if (string_alg::isStringEqual(argv[1], "-2")) {
            algType = RleAdvanced;
        }
        else if (string_alg::isStringEqual(argv[1], "-d")) {
            operationType = Decompress;
        }
        else if (!string_alg::isStringEqual(argv[1], "-1")) {
            std::cerr << "error: invalid format" << std::endl;
            return -1;
        }
    }
    else if (argc == 4) {
        filename = argv[3];
        if (string_alg::isStringEqual(argv[2], "-d")) {
            operationType = Decompress;
            if (string_alg::isStringEqual(argv[1], "-2")) {
                algType = RleAdvanced;
            }
            else if (!string_alg::isStringEqual(argv[1], "-1")) {
                std::cerr << "error: invalid format" << std::endl;
                return -1;
            }
        }
        else {
            std::cerr << "error: invalid format" << std::endl;
            return -1;
        }
    }

    std::cerr << "algType: " << algType << std::endl;
    std::cerr << "operationType: " << operationType << std::endl;
    std::cerr << "filename: " << filename << std::endl;

    bool result = false;

    if (algType == Rle) {
        string_alg::RleCompress rle;
        result = doOperation(rle, operationType, filename);
    }
    else {
        string_alg::RleAdvancedCompress rleAdvanced;
        result = doOperation(rleAdvanced, operationType, filename);
    }

    return !result;
}
