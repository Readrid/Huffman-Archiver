#include <fstream>

#include "CLI.h"
#include "HuffmanArchiver.h"


int main(int argc, const char** argv) {
    try {
        CLI cmds(argc - 1, argv + 1);

        std::ifstream fin(cmds.getInputFileName(), std::ios::in | std::ios::binary);
        std::ofstream fout(cmds.getOutputFileName(), std::ios::out | std::ios::binary);
        HuffmanArchiver archiver(fin, fout);

        if (cmds.getAction() == Action::COMPRESS) {
            archiver.compress();
        } else {
            archiver.extract();
        }

        archiver.printInfo();

    } catch (std::exception &ex) {
        std::cout << ex.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
