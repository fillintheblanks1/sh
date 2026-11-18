#include "shell_parser.h"


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