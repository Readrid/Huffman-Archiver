#include "doctest.h"
#include "CLI.h"

TEST_CASE("Correct input #1: simple case") {
    const char *cmnds[7] = {"-c", "--file", "input.txt", "--output", "output.txt"};
    CLI cmd(5, cmnds);
    CHECK(cmd.getAction() == Action::COMPRESS);
    CHECK(cmd.getInputFileName() == "input.txt");
    CHECK(cmd.getOutputFileName() == "output.txt");
}

TEST_CASE("Correct input #2: one letter flag") {
    const char *cmnds[7] = {"-u", "-f", "input.txt", "-o", "output.txt"};
    CLI cmd(5, cmnds);
    CHECK(cmd.getAction() == Action::EXTRACT);
    CHECK(cmd.getInputFileName() == "input.txt");
    CHECK(cmd.getOutputFileName() == "output.txt");
}

TEST_CASE("Correct input #3: permutation") {
    const char *cmnds[7] = {"-f", "input.txt", "-c", "-o", "output.txt"};
    CLI cmd(5, cmnds);
    CHECK(cmd.getAction() == Action::COMPRESS);
    CHECK(cmd.getInputFileName() == "input.txt");
    CHECK(cmd.getOutputFileName() == "output.txt");
}

TEST_CASE("Correct input #3: long flags permutation") {
    const char *cmnds[7] = {"--output", "output.txt", "--file", "input.txt", "-c"};
    CLI cmd(5, cmnds);
    CHECK(cmd.getAction() == Action::COMPRESS);
    CHECK(cmd.getInputFileName() == "input.txt");
    CHECK(cmd.getOutputFileName() == "output.txt");
}

TEST_CASE("Correct input #3: change name") {
    const char *cmnds[7] = {"--output", "a.bin", "-f", "input.txt", "-u"};
    CLI cmd(5, cmnds);
    CHECK(cmd.getAction() == Action::EXTRACT);
    CHECK(cmd.getInputFileName() == "input.txt");
    CHECK(cmd.getOutputFileName() == "a.bin");
}