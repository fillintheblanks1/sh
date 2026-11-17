#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>


int main() {
  std::string line;
  // repl based loop
  int exitCode = 0;
  while (true) {
    // print the dialogue
    std::cout << "mysh> ";
    if (!std::getline(std::cin, line))
      break;

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
    if (words.empty()) {
      continue;
    }
    if (words[0] == "exit") {
      std::cout << "logout" << std::endl;
      if (words.size() >= 2) {
        exitCode = std::stoi(words[1]);
      }
      break;
    }
    std::cout << words[0] << ": command not found" << std::endl;
  }
  return exitCode;
}