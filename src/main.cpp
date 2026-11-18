#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include "shell_parser.h"
#include "builtins.h"

std::unordered_set<std::string> commandSet = {"echo", "type", "exit"};


int main() {
  std::string line;
  int exitCode = 0;

  while (true) {
    std::cout << "mysh> ";
    if (!std::getline(std::cin, line))
      break;

    std::vector<std::string> words = splitLine(line);
    if (words.empty())
      continue;

    const std::string &cmd = words[0];

    if (commandSet.count(cmd) == 0) {
      std::cout << cmd << ": command not found" << std::endl;
      continue;
    }

    if (cmd == "exit") {
      exitCode = handleExit(words);
      break;
    } else if (cmd == "echo") {
      handleEcho(words);
    } else if (cmd == "type") {
      handleType(words);
    }
  }
  return exitCode;
}