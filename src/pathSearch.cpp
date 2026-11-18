#include "pathSearch.h"

#include <cstdlib>
#include <fstream>
#include <vector>

#include "shell_parser.h" // for splitPath

bool fileExists(const std::string &filePath) {
  std::ifstream f(filePath.c_str());
  return f.good();
}

std::string getPathText() {
  const char *env = std::getenv("PATH");
  if (env == nullptr) {
    return "";
  }
  return std::string(env);
}

std::string findInPath(const std::string &name) {
  std::vector<std::string> folders = splitPath(getPathText());
  std::vector<std::string> extensions = {"", ".exe", ".com", ".bat", ".cmd"};

  for (const std::string &folder : folders) {
    for (const std::string &ext : extensions) {
      std::string fullPath = folder + "\\" + name + ext;
      if (fileExists(fullPath)) {
        return fullPath;
      }
    }
  }
  return ""; // nothing found
}