#include <string>
#include <algorithm>
#include <iterator>

#include <CLI.h>

CommandException::CommandException(const char *msg) : error_msg(msg) {}

const char * CommandException::what() const noexcept {
    return error_msg;
}

CLI::CLI(int argsNum, const char **argsValue) {
    if (argsNum < 5) throw CommandException("Input Error: Not enough arguments\n");
    if (argsNum > 5) throw CommandException("Input Error: Too much arguments\n");
    std::vector<std::string> tokens(argsNum);
    std::copy(argsValue, argsValue + argsNum, tokens.begin());
    std::string s = "-c";
    auto actionFlag = std::find(tokens.begin(), tokens.end(), "-c");
    if (actionFlag == tokens.end()) {
        actionFlag = std::find(tokens.begin(), tokens.end(), "-u");
        if (actionFlag == tokens.end()) throw CommandException("Input Error: Invalid input format\n");
    }

    auto inputFileFlag = std::find(tokens.begin(), tokens.end(), "-f");
    if (inputFileFlag == tokens.end()) {
        inputFileFlag = std::find(tokens.begin(), tokens.end(), "--file");
        if (inputFileFlag == tokens.end()) throw CommandException("Input Error: Invalid input format\n");
    }
    if (inputFileFlag == tokens.end() || ++inputFileFlag == tokens.end())
        throw CommandException("Input Error: Invalid input format\n");
    auto inputFileName = inputFileFlag;

    auto outputFileFlag = std::find(tokens.begin(), tokens.end(), "-o");
    if (outputFileFlag == tokens.end()) {
        outputFileFlag = std::find(tokens.begin(), tokens.end(), "--output");
        if (outputFileFlag == tokens.end()) throw CommandException("Input Error: Invalid input format\n");
    }
    if (outputFileFlag == tokens.end() || ++outputFileFlag == tokens.end())
        throw CommandException("Input Error: Invalid input format\n");
    auto outputFileName = outputFileFlag;

    if (*actionFlag == "-c") {
        cmd = Action::COMPRESS;
    } else {
        cmd = Action::EXTRACT;
    }
    inputFile = std::move(*inputFileName);
    outputFile = std::move(*outputFileName);
}

Action CLI::getAction() const noexcept {
    return cmd;
}

std::string CLI::getInputFileName() const noexcept {
    return inputFile;
}

std::string CLI::getOutputFileName() const noexcept {
    return outputFile;
}