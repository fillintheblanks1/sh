#include "builtins.h"
#include "pathSearch.h"
#include "shell_parser.h"
#include <cstdlib>
#include <filesystem>
#include <unordered_set>
#include <vector>

extern std::unordered_set<std::string> commandSet;

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

void handleEcho(const std::vector<std::string> &words) {
  for (size_t i = 1; i < words.size(); i++) {
    std::cout << words[i];
    if (i != words.size() - 1) { // no space after the last word
      std::cout << " ";
    }
  }
  std::cout << "\n";
}

void handleType(const std::vector<std::string> &words) {
  // no argument
  if (words.size() < 2) {
    return;
  }

  const std::string &typeName = words[1];

  // builtin?
  if (commandSet.count(typeName) > 0) {
    std::cout << typeName << " is a builtin function" << std::endl;
    return;
  }

  // program in PATH?
  std::string found = findInPath(typeName);
  if (!found.empty()) {
    std::cout << typeName << " is " << found << std::endl;
    return;
  }

  // nothing matched
  std::cout << typeName << ": not found" << std::endl;
}

void handlePwd(const std::vector<std::string> &words) {
  if (words.size() > 1) {
    std::cerr << "pwd: too many arguments";
    return;
  }
  std::error_code ec;
  std::filesystem::path cwd = std::filesystem::current_path(ec);

  if (ec) {
    std::cerr << "pwd: " << ec.message() << std::endl;
  } else {
    std::cout << cwd.string() << std::endl;
  }
}

void handleCd(const std::vector<std::string> &words) {
    if(words.size() > 2) {
      std::cout << "cd: too many arguments";
    }

     std::string target;
  if (words.size() == 1 || words[1] == "~") {
    const char *home = std::getenv("USERPROFILE");
    if (home == nullptr) {
      std::cerr << "cd: USERPROFILE not set" << std::endl;
      return;
    }
    target = home;
  } else {
    target = words[1];
  }

  std::error_code ec;
  std::filesystem::current_path(target, ec);

  if(ec) {
    std::cerr << "cd: " << target << ": " << ec.message() << std::endl;
  }
}