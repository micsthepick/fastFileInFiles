#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

#include "fff.h"

namespace fs = std::filesystem;

// Utility function to read the content of a file and search for the searchString
std::vector<size_t> searchContent(const std::string& content, const std::string& searchString) {
    std::vector<size_t> positions;
    size_t pos = content.find(searchString, 0);
    while (pos != std::string::npos) {
        positions.push_back(pos);
        pos = content.find(searchString, pos + 1);
    }
    return positions;
}

// Main function to find searchString in files within the given path
void findInFilesFast(const std::string& path, const std::string& searchString, const std::string& filters) {
    for (const auto& entry : fs::recursive_directory_iterator(path)) {
        if (!entry.is_regular_file()) continue;
        if (!filters.empty() && entry.path().filename().string().find(filters) == std::string::npos) continue;

        std::ifstream file(entry.path(), std::ios::binary | std::ios::ate);
        if (!file) continue;

        std::streamsize size = file.tellg();

        if (size < 0) continue;

        const std::streamsize size200MB = 200 * 1024 * 1024; // 200MB in bytes

        if (size >= size200MB) continue;

        file.seekg(0, std::ios::beg);

        std::string content(static_cast<size_t>(size), '\0');
        if (file.read(&content[0], size)) {
            auto positions = searchContent(content, searchString);
            for (auto pos : positions) {
                std::cout << "Found in " << entry.path() << " at position " << pos << std::endl;
            }
        }
    }
}