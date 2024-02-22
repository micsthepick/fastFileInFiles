#pragma once

#include <string>
#include <vector>

// Utility function to read the content of a file and search for the searchString
std::vector<size_t> searchContent(const std::string& content, const std::string& searchString);

// Main function to find searchString in files within the given path
void findInFilesFast(const std::string& path, const std::string& searchString, const std::string& filters);
