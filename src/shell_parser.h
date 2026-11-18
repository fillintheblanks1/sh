#pragma once

#include <string>
#include <vector>

// split a line into words at spaces
std::vector<std::string> splitLine(const std::string &line);

// split the PATH text into folders at ';'
std::vector<std::string> splitPath(const std::string &pathText);