#pragma once
#include <string>

bool fileExists(const std::string &filePath);
std::string getPathText();

std::string findInPath(const std::string &name);