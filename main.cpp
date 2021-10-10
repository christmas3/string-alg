#include <cstring>
#include <iostream>

int main(int argc, char** argv)
{
    if (argc == 1) {
        auto progName = basename(argv[0]);
        std::cerr << "Usage:" << std::endl
                  << progName << " filename\t\t\t - for compress filename into filename.arch" << std::endl
                  << progName << " -d filename.arch\t - for decompress filename.arch into filename";
        return 1;
    }



    return 0;
}
