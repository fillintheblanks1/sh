#include <iostream>
#include <stdexcept>
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
        // to handle other things thrown with exit
        try {
          std::size_t pos = 0;
          exitCode = std::stoi(words[1], &pos);

          // handling 12abc
          if (pos != words[1].length()) {
            throw std::invalid_argument("Trailing Characters");
          }
        } catch (const std::invalid_argument &) {
          std::cerr << "mysh: exit: " << words[1]
                    << ": numeric argument required" << std::endl;
          exitCode = 2; // bash gives this error code using incorrect usage
        } catch (const std::out_of_range &) {
          std::cerr << "mysh: exit:" << words[1]
                    << ": numeric argument out of range" << std::endl;
          exitCode = 2; 
        }
      }
      break;
    }

    if(words[0] == "echo") {
      for(unsigned int i = 1; i < words.size(); i++) {
        std::cout << words[i] << " ";
      }
      std::cout << "\n";
      continue;
    }

    std::cout << words[0] << ": command not found" << std::endl;
  }
  return exitCode;
}