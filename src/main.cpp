#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

std::unordered_set<std::string> commandSet = {"echo", "type",
                                              "exit"}; // isBuiltin

std::vector<std::string> splitLine(const std::string &line) {
  std::vector<std::string> words;
  std::string current;

  for (char c : line) {
    if (c == ' ') {
      if (!current.empty()) {
        words.push_back(current);
        current.clear();
      }
    } else {
      current.push_back(c);
    }
  }

  if (!current.empty()) {
    words.push_back(current);
  }
  return words;
}

void handleEcho(const std::vector<std::string> &words) {
  for (size_t i = 1; i < words.size(); i++) {
    std::cout << words[i];
    if (i != words.size() - 1) { // no space after the last word
      std::cout << " ";
    }
  }
  std::cout << "\n";
}

int handleExit(const std::vector<std::string> &words) {
  int exitCode = 0;

  std::cout << "logout" << std::endl;
  if (words.size() >= 2) {
    try {
      std::size_t pos = 0;
      exitCode = std::stoi(words[1], &pos);

      // handling 12abc
      if (pos != words[1].length()) {
        throw std::invalid_argument("Trailing Characters");
      }
    } catch (const std::invalid_argument &) {
      std::cerr << "mysh: exit: " << words[1] << ": numeric argument required"
                << std::endl;
      exitCode = 2; // bash uses 2 for incorrect usage
    } catch (const std::out_of_range &) {
      std::cerr << "mysh: exit: " << words[1]
                << ": numeric argument out of range" << std::endl;
      exitCode = 2;
    }
  }
  return exitCode;
}

void handleType(const std::vector<std::string> &words) {
  // no argument
  if (words.size() < 2) {
    return;
  }

  const std::string &typeName = words[1];

  if (commandSet.count(typeName) > 0) {
    std::cout << typeName << " is a builtin function" << std::endl;

  // TODO: otherwise search PATH with SearchPath -> "<name> is <full path>"
  } else if (commandSet.count(typeName) != 0) {

  } else {
    std::cout << typeName << ": not found" << std::endl;
  }
  
}

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