#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "builtins.h"
#include "executor.h"
#include "pathSearch.h"
#include "shell_parser.h"

std::unordered_set<std::string> commandSet = {"echo", "type", "exit", "pwd", "cd"};

int main() {
  std::string line;
  int exitCode = 0; // exitcode for the shell
  int lastCode = 0; // exitCode for the last program

  while (true) {
    std::cout << "mysh> ";
    if (!std::getline(std::cin, line))
      break;

    std::vector<std::string> words = splitLine(line);
    if (words.empty())
      continue;

    const std::string &cmd = words[0];

    // 1. builtin?
    if (commandSet.count(cmd) > 0) {
      if (cmd == "exit") {
        exitCode = handleExit(words);
        break;
      } else if (cmd == "echo") {
        handleEcho(words);
      } else if (cmd == "type") {
        handleType(words);
      }
      continue;
    }

    // 2. not a builtin: look for a program in PATH
    std::string path = findInPath(cmd);
    if (path.empty()) {
      std::cout << cmd << ": command not found" << std::endl;
      continue;
    }

    // run if found
    lastCode = runProgram(path, words);
  }
  return exitCode;
}