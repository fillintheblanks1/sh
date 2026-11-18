#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

std::unordered_set<std::string> commandSet = {"echo", "type", "exit"};

std::string getPathText() {
  const char *env = std::getenv("PATH");
  if (env == nullptr) {
    return "";
  }
  return std::string(env);
}

/* CHECK IF FILE EXISTS */
bool fileExists(const std::string &filePath) {
  std::ifstream f(filePath.c_str());
  return f.good();
}

/* For PATH */
std::vector<std::string> splitPath(const std::string &pathText) {
  std::vector<std::string> folder;
  std::string currentPath;

  for (char c : pathText) {
    if (c == ';') {
      if (!currentPath.empty()) {
        folder.push_back(currentPath);
        currentPath.clear();
      }
    } else {
      currentPath.push_back(c);
    }
  }
  if (!currentPath.empty()) {
    folder.push_back(currentPath);
  }

  return folder;
}

/* FOR WORDS*/
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
  // commandMap existence (builtin) 
  if (commandSet.count(typeName) > 0) {
    std::cout << typeName << " is a builtin function" << std::endl;
    return;
  }
  // try searching the whole enviorment (need to add more)
  std::string pathEnv = getPathText();
  if (!pathEnv.empty()) {
    std::vector<std::string> directories = splitPath(pathEnv);

    for (const std::string &dir : directories) {
      std::string fullPath = dir + "\\" + typeName + ".exe";

      if (fileExists(fullPath)) {
        std::cout << typeName << " is " << fullPath << std::endl;
        return; // Found it, exit the function
      }
      std::string fullPathNoExt = dir + "\\" + typeName;
      if (fileExists(fullPathNoExt)) {
        std::cout << typeName << " is " << fullPathNoExt << std::endl;
        return;
      }
    }
  }
  // nothing matched
  std::cout << typeName << ": not found" << std::endl;
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