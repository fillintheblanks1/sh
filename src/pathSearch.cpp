#include "pathSearch.h"
#include <fstream>


/* CHECK IF FILE EXISTS */
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
