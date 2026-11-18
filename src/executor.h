#pragma once
#include <string>
#include <vector>

// runs the program, waits for it, returns its exit code
int runProgram(const std::string &fullPath,
               const std::vector<std::string> &words);