#ifndef _CLI_H_
#define _CLI_H_

#include <exception>
#include <string>
#include <vector>

enum class Action {
    COMPRESS,
    EXTRACT
};

class CommandException : public std::exception {
public:
    CommandException(const char *msg);
    const char* what() const noexcept override;
private:
    const char* error_msg;
};

class CLI {
public:
    CLI(int argsNum, const char** argsValue);

    std::string getInputFileName() const noexcept ;
    std::string getOutputFileName() const noexcept ;
    Action getAction() const noexcept;

private:
    Action cmd;
    std::string inputFile;
    std::string outputFile;
};

#endif
